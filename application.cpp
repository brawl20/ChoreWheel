#include "application.h"

//std::deque<std::pair<std::string, std::string>> current_tasks = {std::make_pair("Cleaning", "Ꭵ𝒋ǩľḿnȯ𝘱"), std::make_pair("Dishes", "Charlie"), std::make_pair("Trash", "Elise")};

bool accessor(void *ptr, int index, const char** out);

bool first_time = true;
const path exit_save {"./exit.save"};

void App::buildWindow(bool *show_demo)
{
    static bool use_work_area = true, useless_bool = false;
    static ImGuiWindowFlags flags = 
        ImGuiWindowFlags_NoTitleBar|
        ImGuiWindowFlags_MenuBar|
        ImGuiWindowFlags_NoMove|
        ImGuiWindowFlags_NoSavedSettings|
        ImGuiWindowFlags_NoResize;

    // We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
    // Based on your use case you may want one or the other.
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

    if (ImGui::Begin("Application Window", NULL, flags))
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(72, 72, 84, 255));

        menuBar(show_demo);

        RestoreModal();

        this->BuildTasksByPerson();

        ImGui::PopStyleColor();
    }


    ImGui::End();
}

void App::RestoreModal()
{
    if (first_time && exists(exit_save))
    {
        if (ImGui::BeginPopupModal("Restore", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            first_time = false;
            ImGui::Text("Restore Previous History?");
            if (ImGui::Button("Restore")) /* Load file */;
            else if (ImGui::Button("Clear")) /* Delete file */;
            else
                first_time = true;
        }
    }
}

void App::menuBar(bool *show_demo)
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("User"))
        {
            addUserPopup();
            ImGui::SeparatorText("Active Users");
            auto current = schedules.getIter();
            auto last = schedules.getEnd();
            int i = 0;
            while(current != last){
                if(current->User->absent) continue;
                auto color = IM_COL32(128, 128, 255, 255);
                ImGui::PushID(i++);
                ImGui::PushStyleColor(ImGuiCol_Text, color);
                if(ImGui::Selectable(current->User->name.c_str())) ImGui::OpenPopup("User Tasks");
                if(ImGui::BeginPopupModal("User Tasks", NULL, ImGuiWindowFlags_AlwaysAutoResize));
                ImGui::PopStyleColor();
                ImGui::SameLine();
                ImGui::Button("Add Task");
                ImGui::SameLine();
                if(ImGui::Button("Mark Absent")) current->User->absent;
                ImGui::PopID();
                current++;
            }

            ImGui::SeparatorText("Absent Users");
            while(current != last){
                if(!current->User->absent) continue;
                auto color = IM_COL32(128, 128, 196, 255);
                ImGui::PushStyleColor(ImGuiCol_Text, color);
                ImGui::Selectable(current->User->name.c_str(), current->User->absent);
                ImGui::PopStyleColor();
                current++;
            }

            showUserIncompletes();
            absentUserPopup();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Control"))
        {
            *show_demo = ImGui::Button("Show Demo");

            addTaskPopup();
            taskToUserPopup();
            removeTaskFromUserPopup();
            if(ImGui::Button("Next Day")) schedules.nextAssignments();
            if(ImGui::Button("Save State")) schedules.dataSave();
            if(ImGui::Button("Load State")) schedules.dataLoad();
            

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

void App::absentUserPopup()
{
    if (ImGui::Button("Absent Users")) ImGui::OpenPopup("Absent Users");
    if (ImGui::BeginPopupModal("Absent Users", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
    auto current = schedules.users.roster.begin();
    auto last = schedules.users.roster.end();
    while(current != last){
        auto color = IM_COL32(128, 128, (current->absent)? 196:255, 255);
        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::Selectable(current->name.c_str(), current->absent);
        ImGui::PopStyleColor();
        current++;
    }
    if (ImGui::Button("Close")) ImGui::CloseCurrentPopup();
    ImGui::EndPopup();
    }
}

void App::showUserIncompletes()
{
    if (ImGui::Button("Missed Tasks")) ImGui::OpenPopup("Missed Tasks");
    if (ImGui::BeginPopupModal("Missed Tasks", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
    auto current = schedules.users.roster.begin();
    auto last = schedules.users.roster.end();
    for (; current != last; current++)
    {
        if (current->absent)
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 196, 255));
        else
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 255, 255));
        ImGui::Text("%s: %i", current->name.c_str(), current->amtIncomplete);
        ImGui::PopStyleColor();
    }
    if (ImGui::Button("Close")) ImGui::CloseCurrentPopup();
    ImGui::EndPopup();
    }
}

void App::addUserPopup()
{
    if (ImGui::Button("Add User")) ImGui::OpenPopup("Add User");
    if (ImGui::BeginPopupModal("Add User", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        static char name_buf[18];
        ImGui::InputText("Name", name_buf, 18);

        if (ImGui::Button("Submit"))
        {
            schedules.users.create(name_buf, 0, 0);
            schedules;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }
}

void App::addTaskPopup()
{
    if (ImGui::Button("Add Task")) ImGui::OpenPopup("Add Task");
    if (ImGui::BeginPopupModal("Add Task", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        static char task_buf[18];
        ImGui::InputText("Task", task_buf, 18);

        if (ImGui::Button("Submit"))
        {
            schedules.tasks.create(task_buf, 1, 0);
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
            ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }
}

void App::taskToUserPopup()
{
    if (ImGui::Button("Add Task to User")) ImGui::OpenPopup("Add Task to User");
    if (ImGui::BeginPopupModal("Add Task to User", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        auto user_names = schedules.users.getNames();
        auto task_names = schedules.tasks.getNames();
        static int user_index, task_index;

        ImGui::ListBox("User", &user_index, user_names, schedules.users.getSize(), 5);
        ImGui::ListBox("Task", &task_index, task_names, schedules.tasks.getSize(), 5);

        if (ImGui::Button("Submit"))
        {
            schedules.addAssignment(user_names[user_index], task_names[task_index]);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }
}

void App::removeTaskFromUserPopup()
{
    if (ImGui::Button("Remove Task from User"))
        ImGui::OpenPopup("Remove Task from User");
    if (ImGui::BeginPopupModal("Remove Task from User", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        auto user_names = schedules.users.getNames();
        auto task_names = schedules.tasks.getNames();
        static int user_index, task_index;

        ImGui::ListBox("User", &user_index, schedules.users.getNames(), schedules.users.getSize());
        ImGui::ListBox("Task", &task_index, schedules.tasks.getNames(), schedules.tasks.getSize());

        if (ImGui::Button("Submit"))
        {
            auto user_names = schedules.users.getNames();
            auto task_names = schedules.tasks.getNames();

            schedules.removeAssignment(user_names[user_index], task_names[task_index]);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }
}

bool accessor(void *ptr, int index, const char** out)
{
    auto label = static_cast<list<string*>::const_iterator*>(ptr);
    advance(label, index); 
    *out = (**label)->c_str();
    return true;
}

void App::BuildTasksByPerson()
{
    int i = 0;
    for(auto assign = schedules.getAssignments(); assign.first != assign.second; assign.first++)
    {
        const auto data = *assign.first;
        if(data.Task == nullptr) continue;
        ImGui::Text("%8s: %-8s|", data.User->name.c_str(), data.Task->name.c_str());
        ImGui::SameLine();

        //ImGui::PushStyleColor(ImGuiCol_Text, (data.Task->completeTask)?IM_COL32(0, 255, 0, 255):IM_COL32(255, 0, 0, 255));
        ImGui::PushID(i++);
        ImGui::Selectable((data.Task->completeTask)? "Complete":"Incomplete",&(data.Task->completeTask));
        ImGui::PopID();
        //ImGui::PopStyleColor();

        ImGui::Separator();
    }
}
