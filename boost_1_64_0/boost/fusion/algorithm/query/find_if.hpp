/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FIND_IF_05052005_1108)
#define FUSION_FIND_IF_05052005_1108

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/find_if_fwd.hpp>
#include <boost/fusion/algorithm/query/detail/find_if.hpp>
#include <boost/fusion/algorithm/query/detail/segmented_find_if.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/quote.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct find_if
          : mpl::if_<
                traits::is_segmented<Sequence>
              , detail::result_of_segmented_find_if<Sequence, Pred>
              , detail::result_of_find_if<
                    Sequence,
                    mpl::bind1<
                        typename mpl::lambda<Pred>::type
                      , mpl::bind1<mpl::quote1<value_of>, mpl::_1>
                    >
                >
            >::type
        {};
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find_if<Sequence, Pred>
        >::type
    find_if(Sequence& seq)
    {
        typedef typename result_of::find_if<Sequence, Pred>::filter filter;
        return filter::call(seq);
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find_if<Sequence const, Pred>::type const
    find_if(Sequence const& seq)
    {
        typedef typename result_of::find_if<Sequence const, Pred>::filter filter;
        return filter::call(seq);
    }
}}

#endif

/* find_if.hpp
vcn7J7AffApOh0/DJfAZuB4+C38E98Na+Bw8Ap+HH8GfwRPwAPwKvgC/gT+HZ+CLsJ1yfYad4EuwM3wZ9oMHYTR8BcbBV2Ey/CWcBV+HN8LDMA8egcvgG/AB+CZ8CNapawrl3RR80OI+rljWMpTBS+ESOBguhbFwGZwMl4udV8AlsAJuhCvhNniTZk2SvHNCd/IzrEk6KvX6a3gZfE/yeV/y+Q2cDn8L0+Dv4Fx4DObDD2ARPA5vgvVwLfwQ7oIfwRfgCfgS/INn3HTIOyL4jejVCW4Wva4XO8yBw+GN8AqYAcfBTDgHZsEb4VzJfx6shNlwA8wRe+TCapgPD8IF8AhcCH8DC2ADLBT9ioRxDnk/BFNFT+0av55y33MBTIAXwimwN5wOo+ChUMbx1SGOTGQdsm+1f/v+1pHuBOJYw36XiLIWJAYa9y1I5jurdSF5a0KatDakgt/ZrQ/Zzr/Vrglp0XUiVutDjpKHdo1Iw5qQs7JOpLG9DdquDfFrjUgM6dLWhgS0VsRJuprj/u93UL625daJbF4b4tdakX2kazuR/4eN7YNwem1Is9eM9Lot5KysG6m4IiSgtSOB7ovQJZFzoLt2/UjmbSEB741QyW92IIeQk0jYOvoYko6UIpuR/chRpAEJW0+dIElIHrIB2YUcQU4ikbeHOBKRPGQDUos0IP3uoK0iq5E9yPuIYwPnQtKQCmQHchA5gYRu5DfIRCR74//2mpTgETyCR/AIHsEjeASP4BE8gkfwCB4tf3wf6/9zyktzCpUAAC2w/t+1Xv+Mul4/IT0tYXrqlBnTUzWL9S+SvfyrLNJJmADXmv2vBnv38y+1XLOP3CZrOXWZBba2PPOM/dryExb7DziV+b1W+SqLsP2Y6+aZkzsk3LxmP81izf5K/qfSKj+f8/hN+ZnWYR9pbW3XKKv8AlzX3tCIXQdbrNlfjF1rLfNlxqMfdtWe/2CIea1mSSw63aau1dTn4cf5PXZ8dXTgazU9es0JNetVprSndTZ6pfqvV3Iz9u+vDzWv4VyKXlXrPOsnm26vIeH+rSPNttirfxk61Kk6NN02f+jWuA6nYGWrwOdsWs8ltJsTajc3026uot0cT7u5inZzMO3mrgY+B9N6jqHdHFX7OZtXj1G+v/OL3H/0HHNvzxldRi3f8dy0P3vmKsq4LuNSnmEuRaR2DqKkG2iRrpd2Lk8j6Xpo51LY5gu1c34kXW8f52uQdON8pItbZ5+up3ZuhqQb7uN8dXbp5HybaW/97uS9N8I7er99YVo/WKnO92Xye+Hz0vm7tH4u8Wn5589Kg4eg+K8wFvogicjpy0x+KnxUer/U+6o/SueLEv+T6ndq1N80BzH7l7w+pWzxHel9Rva+ovTL7XxDtn4hfEI6H5D4f8y+H/w9Xl+PvY/H1p+TBPHjBBz7K4n8M5HoRJ2PRvXPOGlrm5H9yDHkDBJ1Fz4RJA/ZcFfQLxI8gkfwCB7a5//cs/z8P6+4QHn6b9azv+eZvvK0+kyfkjBrxtSEifJELzH6rh7F3Mj7lTnErAtTcs5YlFOa534n8A2/d7r+LTsnN6uswPvvRdn8XN1fMOzvah4TUpKIujZphrLDoOsctRfwPG/+d1WJHnKOGH0afs75pQzOb3X/Jj91xxF8XX0nwWHxrD4+ljl3ZfIMq1Eg0Jhp42LN+xOW2jyrNywy5xdIXLK4b+2f04+2Nj+nx8WSp0UZA4lN5jn/RLnkTxIbxiMTOH/UEv35pyWkJc6YmBFQjMJ4lw0X6WMVhXr3V+wja0ASSFdpnR8l8r3O1bMmMX6Ukh9tlnBB2FHWZGu+l0bQQ9YlJqjfFxQVLXTH7+sha0wT1X9bklM=
*/