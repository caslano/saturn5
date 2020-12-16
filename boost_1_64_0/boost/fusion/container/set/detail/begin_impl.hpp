/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct begin_impl;

    template <>
    struct begin_impl<set_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    set_iterator_tag
                  , typename Seq::category
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
lzuolXqfofRnL3GvulqfoXJ//wapz1qpz/kr1Mdain7Hf3V9OAfCKXfX5wTM+3m66o/qfv/S/9Q5FvN+wq7PBZn3+3V/nE/zczuu+9man8Nx1V/a/XNEF2znfH78LezBVeuaPlKrYZ93bvv75zHu99++IOOoy/fZtjwu8Z9qOMHi7K/aHKOwPUZjDxyN/XAMDsBYTMexOAPH4RyciHk4Sb3eKN833CDlaa83NpHyQtAfe2Av7CXl9MXRGIoT8RZMwDDMx3Bchf3xPozAtTgI08qX7jpd2TMXy565eD3PXOzFOcCksvOAZa+yV9mr7FX2Knv9X7/+guf/2Q5Xb9Tz/0KUY/zblOf/KZfnhw8aFR0XFnFLVGBc1+4B7PPb8vQij89MR57YkLhugZIpoFvQmAA1T5HLPIFqnrxZrvIE2fL0JY//bNM83btJWf2UsszzhARo8hTMcZUnUM0TOddFHomnP3k855nlCfQPjrGXFaHEY54nKGSMM0/h7a7yBKp5Cua7yCPxDCGPNc80T/dAiWc4eeIXmOUJ8u8ieUYqef5mmqerI+Zo8mxYaJqnm6PuMUrdF5nl6RIUEBVg60cyTlmmix15YqKHjooLsPBS+qBMVMpQ/zYochT/BnTtGjcoPMj293hl2jsNfw9W/t7F0kKmL1L/PjkrITXDmpmZFhnQzT+LQtQ88fmmeXJseaSc82Z5QgKztHkKlpjmUeeTqMR7V8k8gYFdsrR5zpvnUeeToqwvS03ydO2Wpc2Tt8w0jzqfVGUdX14yT1Cgf5YuzwrTPOp80pQ8K03yBEu9JE9egWkedT6ZSr3uLpmna4C0s+QJvccsD+0sfZOylOW+WsljP3uXlspol/K3HGV71Vfpt5TBp/btJV2O1O/8+fW67V1k1KBh/eNYiBbJM0OJ8WGTPCwgR57ZSl03mOShso4885QYHzHJ0zWQajjjyXtM//1RA9Jsp0I3usoTpG47LJvM8ui3QcWmefTboN2Pu8gjZeUp39knzPKw5klZC5XvymZHHr61Ax0hBwSyWVDzeD7pIk+gPc9iZT6meQKDmY+ax+cpF3lkPkuUZWqap5v/kADn71zo0+Z5ojR5zrvKE+jcTmzYYpKHxeUoa5lS1jMmeVjHyKN+vy3PmuShmcmjbluLntVtW4Ple0CdKeM53d9CHH9LVKbT/Y3WknVypdLmhbpy5WcxIIh2UPN4Pu8ij7TDKmU+pnmUnwZnHp+t5nl0y26ryT4Kuw1DbDFLXbeZzacbMTvzFG0zn08/mc+95InfbjafEObjzOOzw0UeiXmN8l3bYVJWYNC/2bsTuCqqPYDj1x3MFHFH3FFxZdESFRUVFRMNFQ3NZEcQkCug4pJLaWJaUWlpLg/LrTIjl1LT1NQ0tReVlZk9tah8ZWVmZWX1fnPv/86dGeay9Ootnw/30+nrHWbmnDlzZrkzc/4jZZZzghfNx6E86nzyXjLJi83R0U5WK2XebTafIDWvdYwTscd0HDWv9co4e03G6e7f0zGfDUrbftl8HMd8NjOOZb/5OeUweV/0cG+LGj/ouMQN/IxUj3SetENZplcM92qMUSvLED/IU2JUGeNWBhnuv9TWxYRJ0cWcC5cYfBMlpuY40tMNLXTykvJJkZh7oHLEsUi5GpdSrpbackkZwLQMhVKGdGVauZbvVZ//HTSUgfwpRLne1+fjYSsDFUoZNHETjfGr5t8s/WMkVto+0ktK+1TLoMRyVX7fZKdMcRx2yxBr0lH3u+zvqFXjNLWRuslOTGc+xetH4uPJ9/QUZ+yhOrbxoiQWXfPqLCs2xD1KeQ9J7CF7XDxbu0rKzEiPTojNjpXy7saSYlJ1PaaPSXU=
*/