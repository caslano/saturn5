//  boost/filesystem/exception.hpp  -----------------------------------------------------//

//  Copyright Beman Dawes 2003
//  Copyright Andrey Semashev 2019

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

#ifndef BOOST_FILESYSTEM_EXCEPTION_HPP
#define BOOST_FILESYSTEM_EXCEPTION_HPP

#include <boost/filesystem/config.hpp>
#include <boost/filesystem/path.hpp>

#include <string>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/smart_ptr/intrusive_ref_counter.hpp>

#include <boost/filesystem/detail/header.hpp> // must be the last #include

namespace boost {
namespace filesystem {

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                            class filesystem_error                                    //
//                                                                                      //
//--------------------------------------------------------------------------------------//

class BOOST_SYMBOL_VISIBLE filesystem_error :
    public system::system_error
{
    // see http://www.boost.org/more/error_handling.html for design rationale

public:
    BOOST_FILESYSTEM_DECL filesystem_error(const char* what_arg, system::error_code ec);
    BOOST_FILESYSTEM_DECL filesystem_error(std::string const& what_arg, system::error_code ec);
    BOOST_FILESYSTEM_DECL filesystem_error(const char* what_arg, path const& path1_arg, system::error_code ec);
    BOOST_FILESYSTEM_DECL filesystem_error(std::string const& what_arg, path const& path1_arg, system::error_code ec);
    BOOST_FILESYSTEM_DECL filesystem_error(const char* what_arg, path const& path1_arg, path const& path2_arg, system::error_code ec);
    BOOST_FILESYSTEM_DECL filesystem_error(std::string const& what_arg, path const& path1_arg, path const& path2_arg, system::error_code ec);

    BOOST_FILESYSTEM_DECL filesystem_error(filesystem_error const& that);
    BOOST_FILESYSTEM_DECL filesystem_error& operator=(filesystem_error const& that);

    BOOST_FILESYSTEM_DECL ~filesystem_error() BOOST_NOEXCEPT_OR_NOTHROW;

    path const& path1() const BOOST_NOEXCEPT
    {
        return m_imp_ptr.get() ? m_imp_ptr->m_path1 : get_empty_path();
    }
    path const& path2() const BOOST_NOEXCEPT
    {
        return m_imp_ptr.get() ? m_imp_ptr->m_path2 : get_empty_path();
    }

    BOOST_FILESYSTEM_DECL const char* what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE;

private:
    BOOST_FILESYSTEM_DECL static path const& get_empty_path() BOOST_NOEXCEPT;

private:
    struct impl :
        public boost::intrusive_ref_counter< impl >
    {
        path m_path1;       // may be empty()
        path m_path2;       // may be empty()
        std::string m_what; // not built until needed

        BOOST_DEFAULTED_FUNCTION(impl(), {})
        explicit impl(path const& path1) :
            m_path1(path1)
        {
        }
        impl(path const& path1, path const& path2) :
            m_path1(path1), m_path2(path2)
        {
        }
    };
    boost::intrusive_ptr< impl > m_imp_ptr;
};

} // namespace filesystem
} // namespace boost

#include <boost/filesystem/detail/footer.hpp>

#endif // BOOST_FILESYSTEM_EXCEPTION_HPP

/* exception.hpp
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
*/