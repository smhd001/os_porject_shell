class shell
{
private:
    const char * history_file = "shell_history";
    char * user;

public:
    shell(  );
    ~shell();
    int start();
};
