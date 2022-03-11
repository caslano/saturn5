//  boost/filesystem/exception.hpp  -----------------------------------------------------//

//  Copyright Beman Dawes 2003
//  Copyright Andrey Semashev 2019

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

#ifndef BOOST_FILESYSTEM3_EXCEPTION_HPP
#define BOOST_FILESYSTEM3_EXCEPTION_HPP

#include <boost/config.hpp>

# if defined( BOOST_NO_STD_WSTRING )
#   error Configuration not supported: Boost.Filesystem V3 and later requires std::wstring support
# endif

#include <boost/filesystem/config.hpp>
#include <boost/filesystem/path.hpp>

#include <string>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/smart_ptr/intrusive_ref_counter.hpp>

#include <boost/config/abi_prefix.hpp> // must be the last #include

#if defined(BOOST_MSVC)
#pragma warning(push)
// 'm_A' : class 'A' needs to have dll-interface to be used by clients of class 'B'
#pragma warning(disable: 4251)
// non dll-interface class 'A' used as base for dll-interface class 'B'
#pragma warning(disable: 4275)
#endif

namespace boost {
namespace filesystem {

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                            class filesystem_error                                    //
//                                                                                      //
//--------------------------------------------------------------------------------------//

class BOOST_FILESYSTEM_DECL filesystem_error :
  public system::system_error
{
  // see http://www.boost.org/more/error_handling.html for design rationale

public:
  filesystem_error(const std::string& what_arg, system::error_code ec);
  filesystem_error(const std::string& what_arg, const path& path1_arg, system::error_code ec);
  filesystem_error(const std::string& what_arg, const path& path1_arg, const path& path2_arg, system::error_code ec);

  filesystem_error(filesystem_error const& that);
  filesystem_error& operator= (filesystem_error const& that);

  ~filesystem_error() BOOST_NOEXCEPT_OR_NOTHROW;

  const path& path1() const BOOST_NOEXCEPT
  {
    return m_imp_ptr.get() ? m_imp_ptr->m_path1 : get_empty_path();
  }
  const path& path2() const BOOST_NOEXCEPT
  {
    return m_imp_ptr.get() ? m_imp_ptr->m_path2 : get_empty_path();
  }

  const char* what() const BOOST_NOEXCEPT_OR_NOTHROW;

private:
  static const path& get_empty_path() BOOST_NOEXCEPT;

private:
  struct impl :
    public boost::intrusive_ref_counter< impl >
  {
    path         m_path1; // may be empty()
    path         m_path2; // may be empty()
    std::string  m_what;  // not built until needed

    BOOST_DEFAULTED_FUNCTION(impl(), {})
    explicit impl(path const& path1) : m_path1(path1) {}
    impl(path const& path1, path const& path2) : m_path1(path1), m_path2(path2) {}
  };
  boost::intrusive_ptr< impl > m_imp_ptr;
};

} // namespace filesystem
} // namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#endif // BOOST_FILESYSTEM3_EXCEPTION_HPP

/* exception.hpp
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
*/