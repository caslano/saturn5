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
QhCR53rKXe+fT853CD6uYOUiLnY9y4Xa4hNDsLmFa8QHlF8/Oh9sdgBfqAPY8HFrBnCikg+Azn0cwJ+V8MVD4JR1fxlf/2mqjUZ1JRdisZI7KgUsuJrmw0uQ/h9Jpz06a87egphR8+x+YHkCpVO8dzlJ9u4WD4YuJx3QykZwreY9CWunqkkIkFToXsSgexH0t1tlYwmJBAdHTBgJo0uBCEKPb4yHDWtwWg9SLp4wlE1a0Fq/wCpiN1CemGIMPa4PS4GgIFKj2pTEf4LBJdV+eYEVP1lC1LwxLIWs/2gmyR1Buh+0usVHRZXMoAty9swDMy7YuSUOSKltvfqBTiZHr1rL6phcy+r28fZe2zxtJG9VWF7FNs9R9ueAXD++uVs4KLGW24qWRSyJ7+YbegioMw6DKSHKx1gSF/DshO9Nvsj3EiX/gjV8NnKU+xlXGpgrUX7hTEIwwUpQocJQIMREfRH7FCUWks+pCGfkfA5wbALvnq9OP7I2tHwij84MEdLDiEi1RCIfDCNBNbmBj2IE9aNpaLhPoHjkHYLAOn4tXUnXEjplp7xHP+9Z2QQtynHtwzEt49pn/M3i2ssqGuHaUf7W4Nqv72gS165/twl6AI7YXdEancz6yOVyuhBxx54mVJuuoVraMqT3QS+x2CGWZPBTe5aO49JHsDtBaxXU9UWpQ1j0NAwhKuOwYRDthESYy6yFzu1maE6jNMP1
*/