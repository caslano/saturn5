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