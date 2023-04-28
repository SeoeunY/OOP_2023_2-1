namespace oopstd
{
    class string
    {
    private:
        char* s;//���ڿ� ������ ����Ű�� �ּ�
        size_t len;//���ڿ� ����

    public:
        string();
        string(const char* str);
        string(const string& str);
        ~string();

        string& assign(const string& str);
        char& at(size_t pos);
        const char* c_str() const;
        void clear();
        void push_back(char c);
        int compare(const string& str) const;
        string& replace(size_t pose, size_t len, const string& str);
        string substr(size_t pos, size_t len) const;
        size_t find(const string& str) const;
    };

    int stoi(const string& str, size_t* idx, int base);
    float stof(const string& str, size_t* idx);
    string to_string(int val);
    string to_string(float val);
}