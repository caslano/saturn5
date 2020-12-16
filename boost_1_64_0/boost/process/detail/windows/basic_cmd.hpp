// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_WINDOWS_BASIC_CMD_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_BASIC_CMD_HPP_

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/process/shell.hpp>
#include <boost/process/detail/windows/handler.hpp>

#include <vector>
#include <string>
#include <iterator>


namespace boost
{
namespace process
{
namespace detail
{
namespace windows
{

inline std::string build_args(const std::string & exe, std::vector<std::string> && data)
{
    std::string st = exe;

    //put in quotes if it has spaces
    {
        boost::replace_all(st, "\"", "\\\"");

        auto it = std::find(st.begin(), st.end(), ' ');

        if (it != st.end())//contains spaces.
        {
            st.insert(st.begin(), '"');
            st += '"';
        }
    }

    for (auto & arg : data)
    {
        boost::replace_all(arg, "\"", "\\\"");

        auto it = std::find(arg.begin(), arg.end(), ' ');//contains space?
        if (it != arg.end())//ok, contains spaces.
        {
            //the first one is put directly onto the output,
            //because then I don't have to copy the whole string
            arg.insert(arg.begin(), '"');
            arg += '"'; //thats the post one.
        }

        if (!st.empty())//first one does not need a preceeding space
            st += ' ';

        st += arg;
    }
    return st;
}

inline std::wstring build_args(const std::wstring & exe, std::vector<std::wstring> && data)
{
    std::wstring st = exe;

    //put in quotes if it has spaces
    {
        boost::replace_all(st, L"\"", L"\\\"");

        auto it = std::find(st.begin(), st.end(), L' ');

        if (it != st.end())//contains spaces.
        {
            st.insert(st.begin(), L'"');
            st += L'"';
        }
    }

    for (auto & arg : data)
    {
        boost::replace_all(arg, L"\"", L"\\\"");

        auto it = std::find(arg.begin(), arg.end(), L' ');//contains space?
        if (it != arg.end())//ok, contains spaces.
        {
            //the first one is put directly onto the output,
            //because then I don't have to copy the whole string
            arg.insert(arg.begin(), L'"');
            arg += L'"'; //thats the post one.
        }

        if (!st.empty())//first one does not need a preceeding space
            st += L' ';

        st += arg;
    }
    return st;
}

template<typename Char>
struct exe_cmd_init : handler_base_ext
{
    using value_type  = Char;
    using string_type = std::basic_string<value_type>;

    static const char*    c_arg(char)    { return "/c";}
    static const wchar_t* c_arg(wchar_t) { return L"/c";}

    exe_cmd_init(const string_type & exe, bool cmd_only = false)
                : exe(exe), args({}), cmd_only(cmd_only) {};
    exe_cmd_init(string_type && exe, bool cmd_only = false)
                : exe(std::move(exe)), args({}), cmd_only(cmd_only) {};

    exe_cmd_init(string_type && exe, std::vector<string_type> && args)
            : exe(std::move(exe)), args(build_args(this->exe, std::move(args))), cmd_only(false) {};
    template <class Executor>
    void on_setup(Executor& exec) const
    {

        if (cmd_only && args.empty())
            exec.cmd_line = exe.c_str();
        else
        {
            exec.exe = exe.c_str();
            exec.cmd_line = args.c_str();
        }
    }
    static exe_cmd_init<Char> exe_args(string_type && exe, std::vector<string_type> && args)
    {
        return exe_cmd_init<Char>(std::move(exe), std::move(args));
    }
    static exe_cmd_init<Char> cmd(string_type&& cmd)
    {
        return exe_cmd_init<Char>(std::move(cmd), true);
    }
    static exe_cmd_init<Char> exe_args_shell(string_type && exe, std::vector<string_type> && args)
    {
        std::vector<string_type> args_ = {c_arg(Char()), std::move(exe)};
        args_.insert(args_.end(), std::make_move_iterator(args.begin()), std::make_move_iterator(args.end()));
        string_type sh = get_shell(Char());

        return exe_cmd_init<Char>(std::move(sh), std::move(args_));
    }

    static std:: string get_shell(char)    {return shell(). string(codecvt()); }
    static std::wstring get_shell(wchar_t) {return shell().wstring(codecvt());}

    static exe_cmd_init<Char> cmd_shell(string_type&& cmd)
    {
        std::vector<string_type> args = {c_arg(Char()), std::move(cmd)};
        string_type sh = get_shell(Char());

        return exe_cmd_init<Char>(
                std::move(sh),
                std::move(args));
    }
private:
    string_type exe;
    string_type args;
    bool cmd_only;
};

}



}
}
}



#endif /* INCLUDE_BOOST_PROCESS_WINDOWS_ARGS_HPP_ */

/* basic_cmd.hpp
jBdikqXeheQX4rvqYg9vYyusz3FvyjheiQX5Mdd5V1ujkzvJNcQbo+8Z9six0cUIvGNwsdT7nZhNDp66hfPNtvBNRpWoJkYe54hB0Wu0TW+qjJcpzLEnWD8d55S5WV+vuMIqGsXuAZ7yRrUS5/8rE3zn//q8QXMtnM8XTe53TC3j67NGtON62YejU1vTZzb2yvq74oukjn3TqrOfbO2plY3tGtHrnJas9dQ+EEXzmnTXPTL2OYat5+vFERWMR91xnjbGJs8G456wekZ5rGC7e1sYrcNjjMLwyo4E9R32h6ScNmlem3Gjxp68N2C9/mJPceSYx87sZXIN6Ug08umXo/pa6xF1rZUWsKsXvW0uL9YfN2AJUOhoyfcwfnYErgOfEf1VZfK5xlqmrrGqUHZ3qeOKtGFSx8B1e8FYcbBqsd3eIeMlVpdfZY2Ur+fS7up+IO2C+e6IOd+p689KvuNcyr0zLU+Vy1yrr8dkX6l3R3JFb25a76B9WpQ7Nt96T5Qr5TXS5cu+YvzFcU32BfVMoQ5Z1IFzjdjIPS75Nk37KaZF9MMVsy/wh9hJjYHl0q6f4j2ch3c4IzwnvJ87j0fWcTaLiTB6ESYRXif8HBNjuMqkG8/FteZOtaqxPj7K2Bkfoes3W+bAttr/YD85Hua4443x7lqqzudFZ4Hrcs42TxgTHE2cDYyxzi68U9PXGO3i2FTXXTeKXtMoX51f8c+3RdZ3OsbcX/I8N0u28X2o3jEZJMfT/NT+1mt/8hB/uuqbnonwqxVyzqd+Nzk+ov/Kcz84hLDEea8x2VWNu9rKxneuSvQ5+vpYXsAM0RzbJvSweBnl8JfbkXI7Sp/fmzZe70t7P5FjZWxV1PVft0a9k6Le5Ron+UxN65Rqf99m7YsGG326ZfU92my5P6yiz0G9Jb422/Gs9aCj7xcLI2sYAzlWGhjvOj52nna7jK/da42NnmjjZcJfPF2MPmHRxk1hJ4zZ3jRjl9fFM9gJjlER4cZ9GPXsIhwjfBERZjgjw4zKkXjyjKwnbahBG9JkH7yYurTknFZQkJ8jQztw7VpN5tN29OIJ7FVq/83x7cu/Gfmfkz76PHU7+UeSf3SyHNcSfz3xw6X8GandiNfvO8nxl4Pxp8xN8l6WeVwwPzJtpal+PCVz4yzWMcK5D3JSCw8zVLK/n3X9orRv2Q5S3vrUCZSXos/Dk4tyC3PUydjcZ5Vul7SOwLmom+yzCvq6/LDsn4d4zjNN8h9I/g0kzfa0mxkTQe9f6Pl8hxw3Hn1M7pHtNkbJ4++aCJvjj6My152g3osZ7n+mlNZNxp91HLM8GPRcY7D0E35kSzzXmMXbMoXyHGIX+c2X/Aal1VN1p3/5jS4eU+jfDw+qc8TTldW5nEceRbljdH9FyPHdRI/xD6V/6muf0Gsf9G0/o7+n20nK6xW1xBFubIzIUvKS13qDjXFy/h1O2R+JviPtFfadzXsn+t7jIbmfOYfODcb9jImd3IlSf3mHybw25NLQcn5LlLpONTxIqmB510Ht8+flmnZ8RBjymkYiNn5tsT+LZox7jGGEQmcHw+dL+DPnBMd+dw2jnWecsc3TxvFt2GSnvueUvFfwVmIzfK2Srx6Xc8rUNk66u3q8jm/Cajs6cd5eHH7e2BbV3egcHWH0iS5nzOY69+LYCFpAXnpOqBkRbSzkO1tJfLvsIr5bVdN4zdHB0Za5+Uo1PsJpa1cZ66tSR9Ffwe/iJKh3DU9Ln36f+jw6FeS9kuBnTyW/bdt4qTrfBt/LqfeCUqTMw6mrSzwz4GGfJY9dsn/M+8H3ZNsreXxMHm9InRLTTlSyzs8TJg4ZWZBnfY/LIffl8XoOTZbtGuw=
*/