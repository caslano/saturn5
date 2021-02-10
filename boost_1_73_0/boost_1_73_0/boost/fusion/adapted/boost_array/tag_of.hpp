/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_TAG_OF_27122005_1030)
#define FUSION_SEQUENCE_TAG_OF_27122005_1030

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>

#include <cstddef>

namespace boost 
{ 
    template<typename T, std::size_t N>
    class array;
}

namespace boost { namespace fusion 
{
    struct boost_array_tag;
    struct fusion_sequence_tag;

    namespace traits
    {
        template<typename T, std::size_t N>
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
        struct tag_of<boost::array<T,N>, void >
#else
        struct tag_of<boost::array<T,N> >
#endif
        {
            typedef boost_array_tag type;
        };
    }
}}

namespace boost { namespace mpl
{
    template<typename>
    struct sequence_tag;

    template<typename T, std::size_t N>
    struct sequence_tag<array<T,N> >
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template<typename T, std::size_t N>
    struct sequence_tag<array<T,N> const>
    {
        typedef fusion::fusion_sequence_tag type;
    };
}}

#endif

/* tag_of.hpp
ClSjRaj9duqW7sxw/HQkuBqsuMWSwcxWw4OS9hqdTMHZJBz3n55YVdmJw01L0EoB1dHWTs7dTlvxz19C6/v3tUVsLC7ubZhs3CNJhgZ0FHWYECtGv/EW/9rSwXC01J2eHFEF1HtoILz+eiP7HkwKpltjm7G2fUHZDiUUqXtMmeYd5xtW76z6DsWzASA4e64gAVtYzNlsI3QbAlNTKiR2lPh4+iGJZ6PReTKOLqOOHd/74g5LUkcPsmp019X7jbP59GI+iuM3V5OhnQrdVqM8O6J5ySvXzmjabXUQtlQ3Ig26gfImvBovvHOes8YKutsCms6o/w+v1Ul7luNURL4Eqiq+2WdNdmvW1Md8tH6BazEdTsexF9qjEiujP8PL2XjkBVXutbPPtdJvR5MRWjZ9TDqR9+3iCf3r0eeD0y7cDUzcfOrtfwXwW2bTDlJV9uAI5gN7RNs1nN62fsKeHLjo3th7NPh2pOPR7FyM2wh3ZnYgYRK14F94/3lBLlzu4fswGoevo3G0uAYhW7bTbn0+WlzNJ/Q+HF+NvDk3+AmgXbxRMn3ndvTi0YjCcTzF8fV6/hAL9VBvpH/v3XA6mYyGiwdb6CviO7j4H1BLAwQKAAAACAAtZ0pSDtATDxoEAADGCAAAMQAJAGN1cmwt
*/