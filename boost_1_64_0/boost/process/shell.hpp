// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_SHELL_PATH_HPP
#define BOOST_PROCESS_SHELL_PATH_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/traits/wchar_t.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/shell_path.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/shell_path.hpp>
#endif

/** \file boost/process/shell.hpp
 *
 *    Header which provides the shell property. This provides the
 *    property to launch a process through the system shell.
 *    It also allows the user to obtain the shell-path via shell().
\xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::shell">shell</globalname>;
  }
}
</programlisting>
\endxmlonly

 */

namespace boost { namespace process { namespace detail {


struct shell_
{
    constexpr shell_() {}

    boost::filesystem::path operator()() const
    {
        return boost::process::detail::api::shell_path();
    }
    boost::filesystem::path operator()(std::error_code & ec) const noexcept
    {
        return boost::process::detail::api::shell_path(ec);
    }
};

template<>
struct is_wchar_t<shell_> : is_wchar_t<boost::filesystem::path>
{
};

}
/**
The shell property enables to launch a program through the shell of the system.

\code{.cpp}
system("gcc", shell);
\endcode

The shell argument goes without any expression. The operator() is overloaded, to
obtain the path of the system shell.

\code{.cpp}
auto shell_cmd = shell();
//avoid exceptions
std::error_code ec;
shell_cmd = shell(ec);
\endcode

\attention Launching through the shell will NOT provide proper error handling, i.e.
you will get an error via the return code.

\attention Executing shell commands that incorporate unsanitized input from an untrusted source makes a program vulnerable to shell injection, a serious security flaw which can result in arbitrary command execution. For this reason, the use of `shell` is strongly discouraged in cases where the command string is constructed from external input:

*/
constexpr ::boost::process::detail::shell_ shell;

}}



#endif

/* shell.hpp
mzga38IJuBCn4Nv4Ci7B+fgOLsFcXIFLcQ2+h9twJX6M7+MxXIvf4SY8j5vxIm7Fm7gN/8QdyDmd9iH648dYBHdiJO7C8rgbK+NerIefYiPcj23xM+yIX+BzeAD74Jc4EA9iOh7GkXgEx+BXOA2P4Wz8Bt/E47gYf8RV+BOuwwv4IV7EXXgXv8R/4VF8gKdRy8dyowdeRk/8A73Qw5/eWAi9sRL6YD30w0bohS0wADthQUzDQMzCYByDITgBC+NMDMNXMRwXYFFcgsVwPUbiZiyOu7AE7sOSeBAr4jksj5dV9zWshB4BHCfQB6ticfRkeetiPoxB5/tKLN7HYaiRH4UOzMEb5KfhTXwD7+A+/AOP4J/4jRrPVfwQ/8CP0FGA7QO9McSL+sNQDMX1GIkbsCR+j5XxBFbHUxiDp7EZnsWOeA674WV8Hq9gX/wFB+KvOBSv4TS8ibPxNi7AyczPcpyGq/E13Ilv4F7s7Tx+4wt4DN8mfw6X4CV8B29hHerzLtZFz4IcX7EQNsJwbIwVsBk2webYCltgT2yJfbAVDsbWOALb4ARsh1OwE87BzrgSu+I67IZ7sDt+jk/jSeyBZ/EZvILP4W/4Aj7APhhciM/pWATjsTQmYB1MxIaYhG0wGXvhQIzFdMzGDJyEmTgNs3AhZuM7OAxX40g8gKPwNI7G8zgGL2MO3sRx+AeOx7KBnC9hRZyIdXESxuA0bIrTsTfOwL74Kg7COTgb5+EifBPX4Vu4CRfgXlyIh3ARHsO38Swuwd/xHfQM4viJBfFdLIJLMQpXYD18H5/DNZiC6zETN+Bw3IjTcTO+hltwGW7FbbgNv8TteBp34Fn8EH/HnRgWzPETK+A+jMYDWA//ia3xIHbFQxiLhzEDj+KL+BWOx+O4GL/DrXgSv8JTeB5P4694Bm/gD3gfz2NgCMdVDMWfsTJexGi8hI3xKrbDX7A7/oaZeANX4C1cg3dwI97Fj/Ee/hP/hSfxPl7AB/gbat7sd+iBD9AHfUM5P8Mg9MMymB9rYEFsiIHYDoOwE4ZgdwzHPlgUkzASB+MTOAFL4CwsiUuwNC7FMrgVy+JHWAG/xop4EZ/EX7AyOgpzXoaBGI11sBa2V/lnsAH2wYaYiU1wNrbCXGyNq7ArrsMeuA+fxRvYGz3C2K+xGsZhA+yHTTAeu2MCJuEAHIZJOAuTcQkOxGWYitswDQ9iOn6HGXgJB+MDzMQCRdjPMRSHY0kcgZXxH1gdx2JdHIedcQLG4ksYjxMxGyfhGJyME3AqzsZp+CZOx0U4A5fhLHwPX8bN+Aruw1fxGM7B7/B1vITz8Decj57hHA/QBxdgUVyIxXExRmEuVsZ3sQEuxVb4HrbHldgDV2EWrsWxuA4X4SZcih/gOvwIz+BuvI170VGU/RqL4Of4JB7CNngYe+LXmIWncCyexhl4Bl/Dc7gIf8R9eBGv4xX8A69iaATXAbEE3sDqeBOb4S1sj7exM27GF3ALjsK7OBHv4WS8j6+j5sNxBD1xJXrhdvTBPeiLB9EPT6E/XsAg/B2DMdh5jxlGYhhWxCIYgxHYGothN4zEeHwCh2JJfBFL4QQsi3OxHC7FCrgRa6NfJO+/WAhbYAS2xGhsg02wHbbH9tgXn8Jh2AnHY2dcjN1wNXbHHfg07sUe+CU+gyfxWbyGvfAuPo8FnuB9GIOxL5bEOKyM/bA5xmN7TMAXMBH74SBMwBRMx1QciWk4EzNwHg7GpZiN63EIHsTh+D2OwEs4En/HUXgPR6N/cfZbLI45WBHHYkMcj01xInbESdgXp+IQnI45OAOn40x8BWfhXJyNy/Bl/ABfxV04F3/FBfgA38aaJdj/sDkuxfY=
*/