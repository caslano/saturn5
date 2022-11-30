// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_PIPE_HPP
#define BOOST_PROCESS_DETAIL_WINDOWS_PIPE_HPP

#include <boost/winapi/basic_types.hpp>
#include <boost/winapi/error_codes.hpp>
#include <boost/winapi/pipes.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/file_management.hpp>
#include <boost/winapi/get_last_error.hpp>
#include <boost/winapi/access_rights.hpp>
#include <boost/winapi/process.hpp>
#include <boost/process/detail/windows/compare_handles.hpp>
#include <system_error>
#include <string>


namespace boost { namespace process { namespace detail { namespace windows {

template<class CharT, class Traits = std::char_traits<CharT>>
class basic_pipe
{
    ::boost::winapi::HANDLE_ _source = ::boost::winapi::INVALID_HANDLE_VALUE_;
    ::boost::winapi::HANDLE_ _sink   = ::boost::winapi::INVALID_HANDLE_VALUE_;
public:
    typedef CharT                      char_type  ;
    typedef          Traits            traits_type;
    typedef typename Traits::int_type  int_type   ;
    typedef typename Traits::pos_type  pos_type   ;
    typedef typename Traits::off_type  off_type   ;
    typedef ::boost::winapi::HANDLE_ native_handle_type;

    explicit basic_pipe(::boost::winapi::HANDLE_ source, ::boost::winapi::HANDLE_ sink)
            : _source(source), _sink(sink) {}
    inline explicit basic_pipe(const std::string & name);
    inline basic_pipe(const basic_pipe& p);
    basic_pipe(basic_pipe&& lhs)  : _source(lhs._source), _sink(lhs._sink)
    {
        lhs._source = ::boost::winapi::INVALID_HANDLE_VALUE_;
        lhs._sink = ::boost::winapi::INVALID_HANDLE_VALUE_;
    }
    inline basic_pipe& operator=(const basic_pipe& p);
    inline basic_pipe& operator=(basic_pipe&& lhs);
    ~basic_pipe()
    {
        if (_sink   != ::boost::winapi::INVALID_HANDLE_VALUE_)
            ::boost::winapi::CloseHandle(_sink);
        if (_source != ::boost::winapi::INVALID_HANDLE_VALUE_)
            ::boost::winapi::CloseHandle(_source);
    }
    native_handle_type native_source() const {return _source;}
    native_handle_type native_sink  () const {return _sink;}

    void assign_source(native_handle_type h) { _source = h;}
    void assign_sink  (native_handle_type h) { _sink = h;}

    basic_pipe()
    {
        if (!::boost::winapi::CreatePipe(&_source, &_sink, nullptr, 0))
            throw_last_error("CreatePipe() failed");

    }

    int_type write(const char_type * data, int_type count)
    {
        ::boost::winapi::DWORD_ write_len;
        if (!::boost::winapi::WriteFile(
                _sink, data, count * sizeof(char_type), &write_len, nullptr
                ))
        {
            auto ec = ::boost::process::detail::get_last_error();
            if ((ec.value() == ::boost::winapi::ERROR_BROKEN_PIPE_) ||
                (ec.value() == ::boost::winapi::ERROR_NO_DATA_))
                return 0;
            else
                throw process_error(ec, "WriteFile failed");
        }
        return static_cast<int_type>(write_len);
    }
    int_type read(char_type * data, int_type count)
    {
        ::boost::winapi::DWORD_ read_len;
        if (!::boost::winapi::ReadFile(
                _source, data, count * sizeof(char_type), &read_len, nullptr
                ))
        {
            auto ec = ::boost::process::detail::get_last_error();
            if ((ec.value() == ::boost::winapi::ERROR_BROKEN_PIPE_) ||
                (ec.value() == ::boost::winapi::ERROR_NO_DATA_))
                return 0;
            else
                throw process_error(ec, "ReadFile failed");
        }
        return static_cast<int_type>(read_len);
    }

    bool is_open() const
    {
        return (_source != ::boost::winapi::INVALID_HANDLE_VALUE_) ||
               (_sink   != ::boost::winapi::INVALID_HANDLE_VALUE_);
    }

    void close()
    {
        ::boost::winapi::CloseHandle(_source);
        ::boost::winapi::CloseHandle(_sink);
        _source = ::boost::winapi::INVALID_HANDLE_VALUE_;
        _sink   = ::boost::winapi::INVALID_HANDLE_VALUE_;
    }
};

template<class Char, class Traits>
basic_pipe<Char, Traits>::basic_pipe(const basic_pipe & p)
{
    auto proc = ::boost::winapi::GetCurrentProcess();

    if (p._source == ::boost::winapi::INVALID_HANDLE_VALUE_)
        _source = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, p._source, proc, &_source, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    if (p._sink == ::boost::winapi::INVALID_HANDLE_VALUE_)
        _sink = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, p._sink, proc, &_sink, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

}

template<class Char, class Traits>
basic_pipe<Char, Traits>::basic_pipe(const std::string & name)
{
    static constexpr int OPEN_EXISTING_         = 3; //temporary.
    static constexpr int FILE_FLAG_OVERLAPPED_  = 0x40000000; //temporary
    //static constexpr int FILE_ATTRIBUTE_NORMAL_ = 0x00000080; //temporary

#if BOOST_NO_ANSI_APIS
    std::wstring name_ = boost::process::detail::convert(name);
#else
    auto &name_ = name;
#endif
    ::boost::winapi::HANDLE_ source = ::boost::winapi::create_named_pipe(
            name_.c_str(),
            ::boost::winapi::PIPE_ACCESS_INBOUND_
            | FILE_FLAG_OVERLAPPED_, //write flag
            0, ::boost::winapi::PIPE_UNLIMITED_INSTANCES_, 8192, 8192, 0, nullptr);

    if (source == boost::winapi::INVALID_HANDLE_VALUE_)
        ::boost::process::detail::throw_last_error("create_named_pipe() failed");

    ::boost::winapi::HANDLE_ sink = boost::winapi::create_file(
            name.c_str(),
            ::boost::winapi::GENERIC_WRITE_, 0, nullptr,
            OPEN_EXISTING_,
            FILE_FLAG_OVERLAPPED_, //to allow read
            nullptr);

    if (sink == ::boost::winapi::INVALID_HANDLE_VALUE_)
        ::boost::process::detail::throw_last_error("create_file() failed");

    _source = source;
    _sink   = sink;
}

template<class Char, class Traits>
basic_pipe<Char, Traits>& basic_pipe<Char, Traits>::operator=(const basic_pipe & p)
{
    auto proc = ::boost::winapi::GetCurrentProcess();

    if (p._source == ::boost::winapi::INVALID_HANDLE_VALUE_)
        _source = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, p._source, proc, &_source, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    if (p._sink == ::boost::winapi::INVALID_HANDLE_VALUE_)
        _sink = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, p._sink, proc, &_sink, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    return *this;
}

template<class Char, class Traits>
basic_pipe<Char, Traits>& basic_pipe<Char, Traits>::operator=(basic_pipe && lhs)
{
    if (_source != ::boost::winapi::INVALID_HANDLE_VALUE_)
        ::boost::winapi::CloseHandle(_source);

    if (_sink != ::boost::winapi::INVALID_HANDLE_VALUE_)
        ::boost::winapi::CloseHandle(_sink);

    _source = lhs._source;
    _sink   = lhs._sink;
    lhs._source = ::boost::winapi::INVALID_HANDLE_VALUE_;
    lhs._sink   = ::boost::winapi::INVALID_HANDLE_VALUE_;
    return *this;
}

template<class Char, class Traits>
inline bool operator==(const basic_pipe<Char, Traits> & lhs, const basic_pipe<Char, Traits> & rhs)
{
    return compare_handles(lhs.native_source(), rhs.native_source()) &&
           compare_handles(lhs.native_sink(),   rhs.native_sink());
}

template<class Char, class Traits>
inline bool operator!=(const basic_pipe<Char, Traits> & lhs, const basic_pipe<Char, Traits> & rhs)
{
    return !compare_handles(lhs.native_source(), rhs.native_source()) ||
           !compare_handles(lhs.native_sink(),   rhs.native_sink());
}

}}}}

#endif

/* basic_pipe.hpp
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
*/