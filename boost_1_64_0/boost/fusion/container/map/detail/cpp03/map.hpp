/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_07212005_1106)
#define FUSION_MAP_07212005_1106

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/map/detail/cpp03/map_fwd.hpp>
#include <boost/fusion/container/map/detail/cpp03/at_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_at_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/begin_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/end_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/deref_data_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/deref_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/key_of_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_data_impl.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
// see map_forward_ctor.hpp
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/map/detail/cpp03/preprocessed/map.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map" FUSION_MAX_MAP_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define FUSION_HASH #

namespace boost { namespace fusion
{
    struct void_;
    struct fusion_sequence_tag;

    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_MAP_SIZE, typename T)>
    struct map : sequence_base<map<BOOST_PP_ENUM_PARAMS(FUSION_MAX_MAP_SIZE, T)> >
    {
        struct category : random_access_traversal_tag, associative_tag {};

        typedef map_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;

        typedef vector<
            BOOST_PP_ENUM_PARAMS(FUSION_MAX_MAP_SIZE, T)>
        storage_type;

        typedef typename storage_type::size size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map()
            : data() {}

        BOOST_FUSION_GPU_ENABLED
        map(map const& rhs)
            : data(rhs.data) {}

        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        map(Sequence const& rhs)
            : data(rhs) {}

        #include <boost/fusion/container/map/detail/cpp03/map_forward_ctor.hpp>

        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map& operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map& operator=(map const& rhs)
        {
            data = rhs.data;
            return *this;
        }

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map(map&& rhs)
            : data(std::move(rhs.data)) {}

        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map& operator=(T&& rhs)
        {
            data = BOOST_FUSION_FWD_ELEM(T, rhs);
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map& operator=(map&& rhs)
        {
            data = std::move(rhs.data);
            return *this;
        }
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type& get_data() { return data; }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type const& get_data() const { return data; }

    private:

        storage_type data;
    };
}}

#undef FUSION_HASH

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* map.hpp
S44DQ39iiP4J9jhA2zG04Qzn/VFl19/g867zvvDXFRUSQ9bsTMXrqC9mqS+O2W3R+fhE+8Kowx4vlC/94wPXOuRGnITeGaZ+T2FGMDURaUtoQx1yElnH/quqv73qb604qAMR688oNBK11DV/RGCfZjbT+z3IOXoHNdk4N19mi0XTvTThYP6Yy1rbEji218Sa58G5UZZ3y1+LV/zTIrstR2XLNNkySbZ4I9pCPGYd+rV+tii/lXIADJItCcibrHvY0ZbsueZjQB36XrGRNr1GLOzf/fVio/3a+epZIeNM4yBhpoMdjIO65D+wHkelzZUXicpawnh4DNvKbfUbjcso8c3Pr7WvQ4+jlrb8Q8ZgzfFEab3Y6uuB2QfL09Gp497aB0dk4xtIE+QQ8grrxFxusdE81kkTlFFQkp9f//O/9djOPLv6PNtC59mzWS9hlqmPTq7e8Xk52Qvrcq5VPHUgJpKsXL6c0DwX70rvpRpzycgUxn9luF5j4NSqsz7jfpxs2BBTPe7badxPw4bY2aYNxQszdGodkzx29NQZKRkT08ZOYdwV84Wmms89sbbxz3M6+osXBmwaGrTJ6yuy2G57prLY+aXsbIWcpf5KoU5vjXZyP2uOj9rttOoqb6FjRPrikVR0ldeoy1vorXVuIGKfBGNlD5t9YtRjXE6jbDmGYs8JtyvNeKau2a6S4ryG2RS+n9zYVTd29f8ndjU+14yxeqWD5+OJFT94+ozZG7cU33Vt7fk5/PN9bO/wPvVcxfRkw07QA7Ud83cRvoWl/ANN4PnQvD5Abcc8XORvdp2h7c6EzWEzy3YHatjuX/r21lewOfzaYucxbdffvl0wprElrIS94c+D2yGXRtbXRHaeJjubWuxM0XYtHLY7W9vFwBjYwrKdV9s1d9juL2rfXxW79TfrfohoJ8XUB2TnKdb9UMN2X0jf39WfX8LgftB20aHbKWbYYCfYFHaWPk7JmnuB2u4MOEfbtVW7OsJsGKuY1U7wRtgF3g4vhE/CeMU+d4V/gN3h67CHNc/C9MjfuvpYMY5HYVvFcsbCTy3bM3cS8Vtdb2r7w7A1fAu2h29bts+sYfuXtP3L2v432v6Adb9q+xEO/fyA7H5QsXo7LXoP16D3Nen9k/S+Lr2HLNvHpEXe/j1NE7yv7T/Q9kcssYeJ2v5Kh9jDx5UH5wnYET4Jx8Ddit19GqYpJvhyWGWxq6oGu36ndr0qu34vu/5gseuYts9wsOsZ2bVXdj0ruwIxxfvgDMUUz4L7VW8iomdinmHC8xSdp3F9PmwJWypGuBW8BLZWPbHIAdXTXvXwb7b3l3OD7dCzK0h1aMe1Ucqfo/F8nfStg/3gesV0Xg+nwBss9XpV7zSHejeq3ptVb7nqvUX13qp6b1PM8ybreFS9gxz22xbV+yPFot4OE+AdlnwlPAuqf8Pzldyl/t2m/V6hGNZ74GC4Xf18n+qrQMpVX0/FsLYw7dW3jrWfJsIOiuXtBifDvjBZ42AqXAVT4Bp4KbwJpsIqmAb3wxnwVTgLHoaz4SdwDjwD/VfATvBKGA8zZOeOKD3/wTfU7nPgVtnZX+fnAbAFHCh7B6n9g+FQOESxt0NhKhwGMxQLna9Y6GVwBLwOXgxvU0x0hWKifwoT4VOKiX5JMdGH4BhLni09P9KW8PwqXtm5WOetIo2fYtgd+nT9LdE4WqLjf6llfFaq/ksdxudyjaMVsA9cqf2/Cg6Hq3UcXwWTYVnwuENmB8cnxX7cjbSs59V6rWpZr1zr9axlvQO1rJfEgZJXSM6XQjdWuaZY5VcHNXHjld145f+peOUdHLN7kSNIjJe2I5nIBmQnsg85hsQsZnwhaUgpUoE=
*/