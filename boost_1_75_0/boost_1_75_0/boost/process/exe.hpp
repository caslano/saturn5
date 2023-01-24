// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_EXE_HPP
#define BOOST_PROCESS_EXE_HPP

#include <boost/process/detail/basic_cmd.hpp>

/** \file boost/process/exe.hpp
 *
 *    Header which provides the exe property.
\xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::exe">exe</globalname>;
  }
}
</programlisting>
\endxmlonly
 */
namespace boost {
namespace filesystem { class path; }

namespace process {

namespace detail {

struct exe_
{
    template<typename = void>
    inline exe_setter_<typename boost::filesystem::path::value_type> operator()(const boost::filesystem::path & pth) const
    {
        return exe_setter_<typename boost::filesystem::path::value_type>(pth.native());
    }

    template<typename = void>
    inline exe_setter_<typename boost::filesystem::path::value_type> operator=(const boost::filesystem::path & pth) const
    {
        return exe_setter_<typename boost::filesystem::path::value_type>(pth.native());
    }


    template<typename Char>
    inline exe_setter_<Char> operator()(const Char *s) const
    {
        return exe_setter_<Char>(s);
    }
    template<typename Char>
    inline exe_setter_<Char> operator= (const Char *s) const
    {
        return exe_setter_<Char>(s);
    }

    template<typename Char>
    inline exe_setter_<Char> operator()(const std::basic_string<Char> &s) const
    {
        return exe_setter_<Char>(s);
    }
    template<typename Char>
    inline exe_setter_<Char> operator= (const std::basic_string<Char> &s) const
    {
        return exe_setter_<Char>(s);
    }
};

}

/** The exe property allows to explicitly set the executable.

The overload form applies when to the first, when several strings are passed to a launching
function.

The following expressions are valid, with `value` being either a C-String or
a `std::basic_string` with `char` or `wchar_t` or a `boost::filesystem::path`.

\code{.cpp}
exe="value";
exe(value);
\endcode

The property can only be used for assignments.


 */
constexpr boost::process::detail::exe_ exe{};

}}

#endif

/* exe.hpp
yY9nj1QcDNqRNji4gMe9PX7PXFUEkbZJTyUnwePmMy3Vnt7c/WJ+/DOiIZU75zZ+sGxvXuFHgkOd/U+Qc7zTYnbgrEqbXOIvzikFBV4Wbx7ueHKyPIhdgqq0DtuEDtmnBc6mqLoCWZqsIZOGubALhaMJ2+A4F9LJcSvm2lGV+TjNYu0xhY1vPISsXthYliIDSUMod6cpbhwe1gnohPNn4gz+j57z3dvyOcX5JZEn6l0o+btkf6CYFE1esgbEi4WF3xGLSgG/0JZCRhzvHmHY59qBkvnDCTBmhCuC5VwgfyDh2vKcBClf//UfMUFSf18D2rjnQAjrE1IV5wDpKvqIpMISkfyI31HhDyWwy78jWq9/ZqwUMAu/O/K0CxSreYZLCYkJlO0FlSSgs5947chTc/hpjb3heL0k/th1jnx5P4I6EuDtnHexuMTnX6MWhb3uZpd7uPOBmuinLI1v5R0AFJu5G/fRotK5uHFez6qGb/ld9bC+HSGvgC8bAm03CsuWYQJTuroxhY+SYZGdtHiY744CdU+9eKNiENt9tAPSEc/oYoRkL17pEHC4cOtshtHsBfq+eCHFK/CM8EQuAod4+qyyJpEcvwt2keIiVH4fYOc5L76DtuzIwDVUP+ePSHb+Dr4Ghm1M6zFgEu4AIHFl5/YaSt+KRXyD/L5S+6J7eEn7/gWJV3/r3bwdSFmJVPnziyu1d1rVQD48fToE
*/