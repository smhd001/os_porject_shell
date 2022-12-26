class shell
{
private:
    std::string history_path = "~/.shell_history";

public:
    shell(/* args */);
    ~shell();
    int start();
};
