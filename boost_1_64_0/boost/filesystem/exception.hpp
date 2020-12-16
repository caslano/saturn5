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
RTavhHxOqJcz1BQdtTOiPsreFacbhqIzK1FPwVoaF05kdwVnAKkqeZepim3OVbT7YFcXArmRkOJbNw+o0VQVeU/joBAPHZfjWGifDLxsyIa0UHAO/Ce3pfevZC8SUsVjVPEXkrHixXrFT5sPFf8+SXaJy7fqSkinEnDCUDQ++DkD+CiyKtnY23QuFAKXzyUCSz0N6OIizhbrJX1R2TEzh2RQE4KYBDxyw/eSaDaOo6AMVKAVkgL7TDRbpEvArTBhBvuegP+hlRPDkI0LmfrgXwHWWexJ5aVhbyn4PwAL+GJdlmUGg3sUmBAtZdSAe7D8q6HjSlEHBUqwDlmoPe2xpTZvPrHlM1gyZGosZ1Aa3l9fCvfX5eg/nBErgeDvgoxXXBs15teweNauaCA6WI75vi0ghK/gCD7kBhtXJU1/A/Xe5GXuWVAzc4DmYi1xOrJqv0qbQQj6LRQL9VHhoA9DDOYLgBEv0Eczgtvom95hJ62MxMzBNNWp5l03h6SpoKN6gjKkmg+iLqnqIOqsD6KPIVO99LzqKRYv8lR6seaDpHSykxh1R2uXo6vHmxV5qJaE2AoeXznJZmpMmIcwtNA1vc6rF2RjwUtfcawE2blu0KxdO6gd9MNgs7CSWlyjK6l6k6Aouhb98tUm/eiyaFdJc2TQvTRDK0GS+gZXZPkyUwmiO/kdX7hdLIOrhlOhijLSbAMOEsqv3ewtrvOSIGHccL/bAVFWq7+NxWjVWEp3l2sQPI/fXd67hplK/Qd4d/nnz6H/4P2E05vFX2JSVtXFP0K8WNunhfZcxErmLwqx4VzDiqaXBm6hPWmkI91BMtims+TEe/Zs9tLAYJcSnJRe/NPiktbuHR3KMoOU+lb9jdYaAitXTdS0eDChV6oZclnwNN0EiHYPopsx469PYtty4dIp4Rlq+hDc8mWUZdySl8OKC2rJaKBf3aOUqUNonRL5EKfLlU0RSFzRa01CflGAh14MxQwKqzvRwAA8PMxpsdfMIUbWEyM/+z4NVzCdkZeexRj5AVse/0Iy4jYAJAn8+rFqlE4S1R6DDD0eJQaueh3PUrYmUS38KFAX1z/FyvXUADkZGK/cGDUFaBKQkwfn9PPe95P83Y5lG14gCVL28aTwSDbc7sLFUwC962BA/UUno1alnTygigXr/0f72dvqB/FJqB/1o+jnDYu5vrSGeqvL/jTzfcjbYXmGtPsgi9JwRzjdhZ0bJvCPvkvjb15Ur038malm8fAZDZhaqeHUkd7FKWTQ6GmXuciMzbklkfZFqnn7Lubvi8kKPx2OW2FCvYtQjblTWojnuYKAiOTHRycWz/O4ams8zjPOa0s8z/Rm+GkntiGe5/MhSzzPe1YlHM+TEQiHrOVfOjnB99zLCJWwvg8kxq9uzcobcm5b+PX6Iiv+rhPawK+bFlnjn65sG79mNSt/WrAN5Xe3lr+vlmO31Z708kLNnsQNRyWwqpU4wXA00MkNR75VDyP4uzCnKd7q/ixVAA4NM41HQZLkjpgbibX48G5hdLgRma+ZlRDvC9h64z+oazE4jaWtZ/feNBHz+2y59SSfBirV+Vh7Z7VSvSoqJmwWM0YWM4YXM4ZV7yhurJI4s86TOAGJI4MJHQIzVkvyVv1JirxlG7ppT5XsWxm6KdSlxPL+/OUwcZqOIc3g7Zc93Iq8bbSmuNBGv424fcXXyG0Xcnul5PaG2Wyj388eWN/OAu2RjpHLDRkB+pm+gvSvAKf5AtEcymim6jRLiObv4zy7QxbEM5L5kztV0Cae9pdkIRNJAUAEZ5dacq7xIJhDdEnLTy8jkbWeVFsBvGKkCty0OBbDjbAMVjkqMg2K/LF6v3X5l/r/fNE=
*/