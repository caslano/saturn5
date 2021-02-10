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
fiD4Qc2m1toPIGxbjwiS5i1VAwY+7BCMaxjFux7Y3U2S15Twrtn+9K9hl6zvm/PZ8Xzno+d76cJwimL4uxv2S+8Qu+k8DuCz489dI6YKl7jsy3Sz8ALYsK9HMerV3DWNaHGurNFpHlwE4VWQhf3M6gDUo4Ur1hhB5mkWnmWX7mUYL0Y83OwbHGfGZVeWLGc4dlBR0uC0kZwOmjQT1wXHT0JcdR/jJ/oGJk4MMreH263bDtqTON9F+A9QSwMECgAAAAgALWdKUmkhGYZdBAAAhQkAADsACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1BST1hZX1RSQU5TRkVSX01PREUuM1VUBQABtkgkYK1VUU/jOBB+z68Y9V7aVUjb3ZOAXXZ1oYQjR0mqJl2oVClyE4f4lMaR7ZT2jvvvN3ZaoNxp4WGDilN75pvxN99MnUUHPvy0x3I0HLz5JOaT4IPr3mki+J80Vf/vkCSP0P6h4wLXd4Tqw7PXY9KDd3k9Qtd4JbtYZ/o9Sd4RbqGT1P/62nmR6FfcaT13/iNebwW7LxR0Rz0Ynp6ewBF8HHwc2HBBKkZLiBStllTc23CWmZ3fCrLZOJJ+s4EqIKVzABgXTILkuXogggK+lyyllaQZ
*/