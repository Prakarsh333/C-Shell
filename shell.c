// To compile the code
// Open the Terminal in the floder containing shell.c
// run the following command
//***************************************
// gcc shell.c
// ./a.out
//****************************************
//
// now shell will open and give the commands to use the C-Shell

///////////////////////////////////////
// Ayush Raghuvanshi (IIIT-Hyderabad)
// Student Id - 2021102037
//////////////////////////////////////




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int t = 1; // maintain the terminal in while loop

char *history[20];     // character storage to store the history
int history_count = 0; // history stored count

void Echo(const char *str)
{
    int i, j;
    int n = strlen(str);
    int flag = 0;

    for (i = 0; i < n; i++)
    {
        if (str[i] == '"' && flag == 0)
        {
            flag = 1;
            continue;
        }
        else if (str[i] == '"' && flag == 1)
        {
            flag = 0;
            continue;
        }

        if (str[i] == ' ' && flag == 0)
        {
            putchar(' ');

            // Skip consecutive spaces
            while (i < n && str[i] == ' ')
            {
                i++;
            }
        }

        if (i < n)
        {
            putchar(str[i]);
        }
    }
    putchar('\n');
}

void Add_History(const char *instr)
{

    if (history_count > 0 && strcmp(instr, history[history_count - 1]) == 0)
    {
        return; // check for duplicate command
    }
    if (history_count == 20)
    {
        free(history[0]); // only maintain the top 20 command given
        for (int i = 0; i < 20 - 1; i++)
        {
            history[i] = history[i + 1];
        }
        history_count--;
    }

    // Add the new command to history
    history[history_count++] = strdup(instr);
}

void Histroy_Display()
{
    int start = 0;
    if (history_count > 10)
    {
        start = history_count - 10;
    }

    // only print the top 10 used commands
    for (int i = start; i < history_count; i++)
    {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

int main()
{

    char hostname[128];
    char username[128];
    char cwd[128];
    char *lastPathComponent;
    char *at_symbol;
    char instr[128];
    char previous_directory[1024] = "";

    /////////////////////////////////////////////////////////////
    // Get the system name
    if (gethostname(hostname, sizeof(hostname)) == 0)
    {
        // Extracting host name from "username@hostname"
        at_symbol = strchr(hostname, '-') + 1;
    }

    // Get the user name
    getlogin_r(username, sizeof(username)) == 0;

    // Get the current directory
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        // Use string manipulation to extract the last component
        // lastPathComponent = strrchr(cwd, '/')+1;
    }
    ///////////////////////////////////////////////////////////

    while (t)
    {
        // Get user instr
        getcwd(cwd, sizeof(cwd));
        printf("%s@%s:%s:~", username, hostname, cwd);

        scanf(" %[^\n]", instr); // %[^\n] reads until a newline is encountered

        // executeinstr(instr);

        if (strcmp(instr, "exit") == 0)
        {
            t = 0; // Exit the shell
            // return;
        }
        else if (strcmp(instr, "pwd") == 0)
        {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                printf("%s\n", cwd);
            }
            else
            {
                perror("getcwd");
            }
        }
        else if (strncmp(instr, "echo", 4) == 0)
        {
            // printf("%s\n", instr + 5); // Print everything after "echo "
            Echo(instr + 5);
        }
        else if (!(strcmp(instr, "user")))
        {
            char username[128];
            getlogin_r(username, sizeof(username)) == 0;
            printf("%s\n", username);
        }
        // else if (chdir(instr) != 0)
        //     {
        //         perror("cd");
        //     // }
        else if (strncmp(instr, "cd ", 3) == 0)
        {
            char *args = instr + 3; // Skip "cd "
            if (chdir(args) == 0)
            {
                // Directory changed successfully
                char cwd[1024];
                // if (getcwd(cwd, sizeof(cwd)) != NULL)
                // {
                //     printf("%s\n", cwd);
                // }
            }
            else if (!strcmp(args, "~"))
            {
                const char *home_dir = getenv("HOME");

                if (home_dir != NULL)
                {
                    if (chdir(home_dir) == 0)
                    {
                        // printf("Moved to home directory: %s\n", home_dir);
                    }
                    else
                    {
                        perror("chdir");
                    }
                }
            }
            // else if (!strcmp(args, "-"))
            // {
                
            //     if (strcmp(instr, "-") == 0)
            //     {
            //         if (strlen(previous_directory) > 0)
            //         {
            //             if (chdir(previous_directory) != 0)
            //             {
            //                 perror("cd");
            //                 return;
            //             }
            //         }
            //         else
            //         {
            //             fprintf(stderr, "cd: previous directory not set\n");
            //         }
            //     }
            // }
            else
            {
                printf("No such directory exits.\n");
            }
        }
        else if (strncmp(instr, "cd", 2) == 0)
        {
            const char *home_dir = getenv("HOME");

            if (home_dir != NULL)
            {
                if (chdir(home_dir) == 0)
                {
                    // printf("Moved to home directory: %s\n", home_dir);
                }
                else
                {
                    perror("chdir");
                }
            }
        }

        else if (strncmp(instr, "history", 7) == 0)
        {
            Histroy_Display();
        }
        // else if(strcmp(args, "-")){
        //     else
        //         {
        //             if (chdir(instr) != 0)
        //             {
        //                 perror("cd");
        //                 return;
        //             }
        //             getcwd(previous_directory, sizeof(previous_directory));
        //         }
        // }

        else
        {


            printf("***************************************************\n");
            printf("Invalid Instruction\n");
            printf("***************************************************\n");
            printf("user: User of the system.");
            printf("Valid Commands are :\npwd : Tell you the path to the Current Directory\necho: Only 'echo' command is invalid you need to give some augement with it.\n      example-echo This shell is awesome\ncd  : 'cd file name' change the directory to file name,'cd ..' will get you to the previous directory.\nexit: This command will end the Terminal.\n");
            printf("***************************************************\n");


        }
        // add command to history if the command is not history
        if ((strcmp(instr, "history")))
        {
            Add_History(instr);
        }
    }

    for (int i = 0; i < history_count; i++)
    {
        free(history[i]);//only storing the command till the terminal is running after that free the space stored in history
    }

    return 0;
}
