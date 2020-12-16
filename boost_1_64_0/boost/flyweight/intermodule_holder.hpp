/* Copyright 2006-2011 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_INTERMODULE_HOLDER_HPP
#define BOOST_FLYWEIGHT_INTERMODULE_HOLDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/holder_tag.hpp>
#include <boost/flyweight/intermodule_holder_fwd.hpp>
#include <boost/interprocess/detail/intermodule_singleton.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

/* intermodule_holder_class guarantees a unique instance across all dynamic
 * modules of a program.
 */

namespace boost{

namespace flyweights{

template<typename C>
struct intermodule_holder_class:
  interprocess::ipcdetail::intermodule_singleton<C,true>,
  holder_marker
{
  typedef intermodule_holder_class type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(1,intermodule_holder_class,(C))
};

/* intermodule_holder_class specifier */

struct intermodule_holder:holder_marker
{
  template<typename C>
  struct apply
  {
    typedef intermodule_holder_class<C> type;
  };
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* intermodule_holder.hpp
AxWq934IFJGgPJtuQkOHKvm/zcK9gp6v7nT8ODwb/E8U/5evigasZajEHN7XnrNxl+jc8OMdzGbzxSaz+WAvGtk4EER4LmmbfU4KP8+6wrcHfrFJgqX8o5rJP86RjSw23I+ijVwwJqpHpgnjiBUuFWpQcWNPVYz6s2ge1WAqthCf/PBEW0dxQQ2zG1Z1mDtAsCRVpNDyCtKO8myBOrK4yuTXoRUPhOwiU52iuCu+MIGt6a/35oH7tBPbQgIhvUJvEgDD4N+s0ILb68LqPcaU/IXVb/GUpcKAnskbaF/lEVjc8oD5a+hnm5aHTckzqCuIlZaXcUvUKw/MygpaYSXm6WIoXcxLT0Upw/mGLD9k9cDl8HtiI0i+0LMutIWvYwMQpgODEZaJDFdHp7AA6JzCj2Z0Han2IvqMPm6D+MVlbCYZKfJy7G/gR0hj16nrvNJSTr+aXZaOeZnrNTdm8qWrhKboo29EEDGH9vMRBv/gIFTKzQlHIqzMgUS+El6O5XLkPeESIrzjFwzfadQbKMrAbuAgfXENQD1FGqTh5+B0pUjbU8xc6MbkX7RUHJNf0+uN8yxprrNauLL2yaONnGtVtdKWQl2Rig0rktVFSt0/RmuHg25UfkFiED2rsjVfQLC+WkFFgC4Kss+IqwAuFAFcKIrlQvHyUbbz53KLkNzyFBGjejas3iK1bAJ3AHgRrSZ7R3IjIJL6b8NX5HkLQq/yOInjAzU4UG5ry0MyngrY2PIzJ51d0pyT1NiZ8ztFytVsPHDAQy43CMX3AmZTTPVnzl9pWIfcWhgkNPIdieHr0mPKuiS/DJ2fsYforQDfsAEZSYRlOcd6V3flfYfDoTi7kb3pL+Bo0XcYFpR9+gz8Mxc4qM14ME35VVdF+z8a31by2O4jopw+kHcE/K4vS50uDXA2PkKjy0k+m7ZFFZI3zW8UaxekcX5jWmi8SHs8TQkYzU1S2+9lK4qf1i3hj+DLXZhKViSFKAF30a0CJwH1TyD+OyAk5eE2OLwpDb/vMdD/7rJzH2vfMF20TWEIqYGUoIcgKzBIkP0sO1LI1mO1HdVL7Ue8L7CKx3we0cP0deK2Afdjv/HbCN9zoBdJ6UuBieARp8j1ZzdE7PrGsLIn3znUdD9UlasWcwFqibxm+bZT2DnlOsvK2RNJLHHLq+WZJZiZx570zGUiE9pGcjQmj3xiHIVkJfQzcUvG0jMUgyePlNuUSMPt8FBZ0QBTRacJUFlYgHrUOzKW8lMapyUpfBKcrZuEz09R7Y9IbrqDPevm0PVjVW/STyDulUDQg03NOOkk9vtkXuFNVKFIzxSVNqXVKmHFagk8GxXsavqeZGmyL20jDx+tV2S7qeGnG6dFIiDb/F9VuyoMpPcMGqqqwrHCjZpSS+3oLanKrC4UFm5ZdOTBgSCHemMJu+DIV7gc82EqXQcJz2bpJrOATL1A44ncpAC87eata0+HUuXw9XoqVLcCyhiv9xTqJjJR7cDLsgw3Q5u56AqApgqZT7NORor8ZDe8RKoory0wGtmOoqUDYHOC6XIwZofdwpoqb12y0P0rhLdLFaZ0FNY5V4kb3/9Mdj8BHAekcEivcvfsPbeEfNwie81hGJCUfas4/Yt1dbOa4OPyAbW/LCUNnK89i7pYVzZl64fiqE6+BCinD7gEuJzjqhE6tj/zKevIION6Toxij7MplJ4ysmfR3CD1mLhG1fSa2C6JL1Gn6GuiN5l3mmQMfNqAFOnHfiOVei+RQ6ZTiU3DGyJSQciOx3NBHEJlW0MtNgOn2fyZ+2f/aXZEL6Qty9G6JQpV8zyamkpejyTRemqWX3ZxkfbWGNYLBbx7W2nPJ4jFSAjmcAZQoy8=
*/