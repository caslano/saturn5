/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REMOVE_07162005_0818)
#define FUSION_REMOVE_07162005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct remove
        {
            typedef filter_view<Sequence, mpl::not_<is_same<mpl::_, T> > > type;
        };
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::remove<Sequence const, T>::type
    remove(Sequence const& seq)
    {
        typedef typename result_of::remove<Sequence const, T>::type result_type;
        return result_type(seq);
    }
}}

#endif


/* remove.hpp
IuBqYlXtlEAB7NHASENxfbCpZDikb606ZknZapoNzhRc8SwKpFD6xQKXuRkjb+kMN46TMunk0FYQdlPS8IVjSKUc90Scpxd2XaYXfiBQ/8LjH/T2wo88+F++8Byd0j5QTUizS83IdQiCOJyTa7g1ZRm2i37VPJAKcpPncVNKYZL+bd/hn3et+Lzh2rdtyt92egBPF4kZUnfLD9nJYeEJGNmSjDpY243wCyprF7YBcGCATGkLL2hEBJfGX2m1+kqrxSvJ/JXiuXOYWL9vAg8V8DFAKwymrKQRcbYb3Xqb1OEVpyOvqXX49zOVVGM4x/Ic/g1rN2BMhxZPRk4Vj3ikitqLhKcpRj1VDMrxRhUDc/47qqh7xlTWFjRcP+dZHBvIYZQz2VPDuPKFDX9mmL/DR2qGJw1qOV/est3U1NxJk61RN7clTTVa04q2opemUkkR16ohk8Radd8kWqv68OOJ58ACccxOZweeo2OnSbiStaXDdbxvNJ02oYOBDivseFjCR3jxOVoD+enRp3n863Mi52xSYlXxThfDVig6yUD+8qQtGvsrEUvw5L3KMgnzJIuJxqB+vugyDxmiOBk8NJAXQQFSeJMWySdCcZG8MRzVnds3N+NuTt9nk1os12UOH8K/TK588q5ICnTO5mGZlx497+KGdfRC+IOf5xq0se4QEoVxTa+gIXSeiMLDhYlJFNZMECEgOzvG4ZHQnGrt
*/