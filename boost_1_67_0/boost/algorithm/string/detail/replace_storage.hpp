//  Boost string_algo library replace_storage.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_REPLACE_STORAGE_DETAIL_HPP
#define BOOST_STRING_REPLACE_STORAGE_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <algorithm>
#include <boost/mpl/bool.hpp>
#include <boost/algorithm/string/sequence_traits.hpp>
#include <boost/algorithm/string/detail/sequence.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  storage handling routines -----------------------------------------------//
            
            template< typename StorageT, typename OutputIteratorT >
            inline OutputIteratorT move_from_storage(
                StorageT& Storage,
                OutputIteratorT DestBegin,
                OutputIteratorT DestEnd )
            {
                OutputIteratorT OutputIt=DestBegin;
                
                while( !Storage.empty() && OutputIt!=DestEnd )
                {
                    *OutputIt=Storage.front();
                    Storage.pop_front();
                    ++OutputIt;
                }

                return OutputIt;
            }

            template< typename StorageT, typename WhatT >
            inline void copy_to_storage(
                StorageT& Storage,
                const WhatT& What )
            {
                Storage.insert( Storage.end(), ::boost::begin(What), ::boost::end(What) );
            }


//  process segment routine -----------------------------------------------//

            template< bool HasStableIterators >
            struct process_segment_helper
            {
                // Optimized version of process_segment for generic sequence
                template< 
                    typename StorageT,
                    typename InputT,
                    typename ForwardIteratorT >
                ForwardIteratorT operator()(
                    StorageT& Storage,
                    InputT& /*Input*/,
                    ForwardIteratorT InsertIt,
                    ForwardIteratorT SegmentBegin,
                    ForwardIteratorT SegmentEnd )
                {
                    // Copy data from the storage until the beginning of the segment
                    ForwardIteratorT It=::boost::algorithm::detail::move_from_storage( Storage, InsertIt, SegmentBegin );

                    // 3 cases are possible :
                    //   a) Storage is empty, It==SegmentBegin
                    //   b) Storage is empty, It!=SegmentBegin
                    //   c) Storage is not empty

                    if( Storage.empty() )
                    {
                        if( It==SegmentBegin )
                        {
                            // Case a) everything is grand, just return end of segment
                            return SegmentEnd;
                        }
                        else
                        {
                            // Case b) move the segment backwards
                            return std::copy( SegmentBegin, SegmentEnd, It );
                        }
                    }
                    else
                    {
                        // Case c) -> shift the segment to the left and keep the overlap in the storage
                        while( It!=SegmentEnd )
                        {
                            // Store value into storage
                            Storage.push_back( *It );
                            // Get the top from the storage and put it here
                            *It=Storage.front();
                            Storage.pop_front();

                            // Advance
                            ++It;
                        }

                        return It;
                    }
                }
            };

            template<>
            struct process_segment_helper< true >
            {
                // Optimized version of process_segment for list-like sequence
                template< 
                    typename StorageT,
                    typename InputT,
                    typename ForwardIteratorT >
                ForwardIteratorT operator()(
                    StorageT& Storage,
                    InputT& Input,
                    ForwardIteratorT InsertIt,
                    ForwardIteratorT SegmentBegin,
                    ForwardIteratorT SegmentEnd )

                {
                    // Call replace to do the job
                    ::boost::algorithm::detail::replace( Input, InsertIt, SegmentBegin, Storage );
                    // Empty the storage
                    Storage.clear();
                    // Iterators were not changed, simply return the end of segment
                    return SegmentEnd;
                }
            };

            // Process one segment in the replace_all algorithm
            template< 
                typename StorageT,
                typename InputT,
                typename ForwardIteratorT >
            inline ForwardIteratorT process_segment(
                StorageT& Storage,
                InputT& Input,
                ForwardIteratorT InsertIt,
                ForwardIteratorT SegmentBegin,
                ForwardIteratorT SegmentEnd )
            {
                return 
                    process_segment_helper< 
                        has_stable_iterators<InputT>::value>()(
                                Storage, Input, InsertIt, SegmentBegin, SegmentEnd );
            }
            

        } // namespace detail
    } // namespace algorithm
} // namespace boost

#endif  // BOOST_STRING_REPLACE_STORAGE_DETAIL_HPP

/* replace_storage.hpp
HjBW6d449qxe48tG1qFeX6oKpfNyzDgcDq+yDaTLMpBbfpHJAvxfYDhQZ7Iy3cRPhsoB2Vawx1yPuKdLOvjAbjklD7/IuM+ae4zxCnAC+gjxH44lyPWgXkZNa11s8s6CBbvZSIAX8hJelEKmF2KFc9DpErZFXmCBJbYQj9AgfoA3auFp5+btkOShT5OKd/qJ25bqOSrAnn4xmAl7iSo94vGrcqxtSj4hvRSeC4HuIJVjDEyuDgjZ//lEa0tXQmoZeqvu0wq4tztbZPd7fzNTImdhvsCiHcNI3HeiaYDJlW92ZAJdUdxm4PstE5BDLQ6GZAK+PxVXLuT3XspwXxM3SZEJukdf4U/vSjy5TcF33Z6QTrGz38XyP/mZD/IPtyq/uZe8TkUrpgHuC5hWwW7eLdSF6H1tOgz03xy8f7HqIQYE3uB64plr6JOYGT340LjxAir9EtjBe7Q4NUMBbPQWNV/owZ9oAZUVCUZIvXnqgBbZrF6JS0k9iCkIA6XwlOeTPHKlDlyB7JCFomz+uw/Niwl8czhbESj8IS02Xuzgv2DtkZMHa74izZes+B6k9+6dPt5wc03O4weTwGDA3DoBYvjfh+BJCoI4e5AglhymUwB6Ym28I72+wMGTNsRVKFBKg7rx2WmPTlUlUV9agzw5MU5G+2loK1WT2TNl62Sd2w29GiJBciaU71BV4dQNtjU23UgmKCVUKTUD9o48IfO5434Gj6gQXYL6gjONTjWeww/lafu7gd2XkAZ6CJdV19Ubzrt+YxL/BvXDk3fLXuQlsRFX19Gv8Qgm6VL6Ql52JBkG481zG/wNp60zMDPqP9rX5OQ+liTMzkEZJzxBNLpwpyFcqkbzZIn0txpLeNpQ0xOkM3ynF7BWYJK2gr+/Wf5KL6HTDvvUxj6EEavJMb6aFCiULvTCW3Y3Qhi7RnjwCMELJsZhE3wTgE/2faXN4mHNn+OjsdJRo1liA9CZP84gSq6PL7U9JN42HLpLXb9exUpSbaT7u9dQT0UJsMO/U7473Flx/0P3t1BnyZr1vUmBCeTQ7IEbXx0uPEDX6umMzqC+9cmJlSFPT/8h18lzM+mu0mOlSLF+wk2BTg64EaTtGOEzn//p/ayPXx+eHzGq8tL7FwvmmdmNQafPRGkYq7snOzbQukJ+assiwZQ457zGzd6EmPRiATrpsRcjToV1TKmNjc/Mog5PbVA3OLQvkPrOPIfgbfpfd3wY/XmToXcwaoKebgF4MlHiXt7L9xNLXzsC2Q1fePyZASPKt6deww3KV999yh6yvMwKR/C/OqQ23m6lkqs1cENNcPUBr5UvaOaD/HpDbn/ZPEs+Ub/QG5nfYDRPquCaxPAj60O423Ih+G7YYhSo9zbwAThPxc0+8+Q4ov165I++s+1zW2kzffRM47h8GuHPMrtH8rW2zCy6iAPqzdyR9OmuOXG+BnQCjRF3jD/NIrysLuEOrGmVXChO4Bd+dgype2q5TkDn9hHieKhrfuUbWwa2TO4/wdhP2mfBc9mTyNR/55O3Z4k1JKsTLOP4NDX5Kh5b4w8EzGXKSLxYQzTeZ6KQ2IktRdiHIKy9yBIBDsvf7Cc905OL/XvaX+j9V7ihRqgp7Z9eXwEEEPk9sGrY3BrNwB+vsFsmS7knwt9IEIYLESxaS/ZSk+E7VtHPN5zW2UrujTpfW57v/FbpX+06b/0s29HPI/WwVs1udwuaV182vWzuOKEmNNNVC98FvHf0Ad8C81f/WF0HNiBl9Vj5iR7Ch8ppgrpt8kkWiS6wqQwhdeCSvf59dtYMEyviSQM/JYFyNBl+EU2Rn9RiYmamEzfl5rGTewwNjxE3to0+uc37VtzJ4f2lZqh9Xa9MoORk7LL4g/fwRdm1MwgxlRwq0Y7EUjKgM7lDOROa7WfI7ui29TkUwH/xHraGoFLm3nd43h1RyXUCoobo1gtsofnUpnYU0I3l3z692fy8dISC88CU5PdN12J19NX/dkleixMoDZ95fY1RhrNwtVeIugl/+12/9jbD/V3YshM00hc7k5xWTqjJ0ZW6EF1/5VgoR8zes8tIu0fvKJ9q6B7OBKPb2QgGmKU9feds+Zqzds6LonuDQbdYHOAJ0prTxJUA7o0m+Sr9dm3+hwJB+gGh5bph9nsE/xCCJzCFd6dZIiPL94XsOQjHP9l7Ni2g78khVMDWP9kL+1MCWgA0RL7kfvwHw/oKeP7Ssb64tf5Nnf4d/B/pZL/4bGra8UtJfSenC3pQ2mvmniwUICu60gxRp6T/+pCLE5j0CSYmgF1YK/gRvccpQ+nYjbvaIMXtV9Goecho6JmEUI7sJ0dk/4gEbFGa1jhfWWgJZUnig1kaf++D46pvvrXPpTYAgqpdOInuhxYnsEMfx75tQiW6aOLOfsFzJNcAvBNCiD67XVPGUOeEwR6eG4I6lzJ+/87mDJsccteJT3bytrKDXbME8mTjjehDBo/iINWnmoqshkGkQt+RaDnn/YI59MTm2xuBEWKnCfmSgfQdIJWDI17kDmTPB55bXu4mfmg+ikheShe5pgxndosU0M4J6xxhrNoMHtLOd7ZvAA8s8NN16tirZivW60L6Uy9+9fjGdsvHK8ZLGxUGRpmvGau+N1/n2lgsBitqoGqNklvcb3KSV89fT5+rxnxK/VboH1oaMF9d1XbsDl8d5EkvTwa6s/buFp0Hske7T1O+VK/wOYLvJ8mCynddJfih7VGXFtutYyWYDvvElV9W+tf863ThrabyCpEHRE45LLxq9U+LpLNSX4LKHiSQa2WDypa8QQBf4Faf8ulS5mkKKHnC7UPVRXuw7Z3uj9grN2TbTDYJspXmheayiUzDnNNgF6ylDKXV5lp1CX9ciWWCtnWwz6tE5HSasDY0zrXCDXjmynBhA+DndIuF/uwyXdtLhdCUGf3v5lq+N5sxvBafqHJvcJl0L3FTYve5CqaxPIGfR3Wq71SW5MiMc4b8ctsv7lZynakLcsX5ZA70Spx7KMvjhT49M3gZ1xfaBH15/ySC9ZqhHzrJ4z/51Mnza71HZ6YvLUGfaP106Wv7LyKSrcyolx+aNe+/PDYjOS5Nyg+uZvkG8Emdns6OuXzpzDG6tfGUzQnPwPUcDCwp6UkrseH0feebhnj5CzYEZonDrLuE7B6+eVYvpxGct7NP97Fo0fGwCZrwuQh1l44PxjuP51EmnnmT/1Bzc8MksMrszkE55r377SviwYqR/fvo74wc0INbGDiB/y+RO/Hcm9clEV8iiKEqEcJI44Sum5p0KaciVxGOnJwbI3nkR/Fvp/yXmdRuL/gU65LLLMQIErQzmZkiE6JaAUxesWiFvPfQFmksuVQzcMsSGcRV8TwP0DNYmgMzHfVLVM1jz37FINEPFlJfKeRfzZRFPiZJOM2ozxHSCqa1v5XN+4ZvgTliJ6BFSB4uK1FRWLSGZhGFMmqhp+mc7001J0OK2CFjUiG8+mlEjc/ZfHn4dSAPV5Kqm7PRcrb8ZCqdVriJc4ZA2OXdb4H5Jq6hCwWDj+wkAt+zBrAMKVjFvInjoDfxCG4Rm5e9D8U0p87VaNvCbJUqjO26Wk/G2Xi4O+l6AI2oezq1/GaYcDwgE2CfaJvLy+AyUeNwZi7JVkVcXxvePJiqyjTTdz5gk0tzw2nLUt5nDplwOMDHaUtQfvEXvq09hG4TvnU9SGar4jq1m+rPw9VDoMlgU76HwF3xSIHuHXruE6eJh/ETFpAlcJLE3IorDFcBn4tXHhYiL4FVmhdYXfw0RO8mdfWFm1EJzM/HGGd3/AvQSjIqgQpCB7oI/XsTitSAP12IGXWml5MErgJpbMpwRU5JIX2BNT+Gh2sW69CmOChvn2cbphx7TkXO9Ps61Td9UVPhqHVel+fZBJ+tZ/mLROx3SufNuWseOZ/8tYDr0nnZUHJW+8LZ40C/lAxdqyJlo6PWsFiqkERaSnxMJJWwBCmH6q9rXXIIfCW/Wicy7rZ0KwSYkuTaR7JmfF6AyU+da5Ap4dyk6Nw2WRCH0+fVDbiYq25e3J3Koqbb7ZGOv8aCcNprLCXoh7B37MtdfyVyM+EgLXIBo5Q6fwbihcbDXn1HAdp4R1vLQ+kAD+SlxMr4Uk8bmxaGKwKsyhK6p366lVNT4u+qcNuUi2KqctXLFElnpqNxraFzMMlL+xQri7eJU53zUq+rFWZLtBSsKLvmFTgVTW1rIsYk8qBxnzaTOl65SRSd1jf4a2cRxymZiZhI/fDN/5HXJnj/y98GITPslM9zPekV/cz3241Sy1kF7rPUrYmWV/QNtN46X73uM6+Pcbfkka4lrq9FZ+OxfKcV5S6N60bHCKbLqySyVPTBNRMOZdpOf7IlbWKFU3ajdvvQ/L4Kr+swHMVFjnPp5DMfNT39bgZDyxh7fXl9+c1ckElXfvlRkOo8adOeapKPd1043OY3EKeTlZX3zojlSDl6UtJNmGpKikokdYayuqJSlm95TsJh75pvwki51ZaHvm8OT3fN6hBIc16VVbXBqp27qIP9UaOEw4OYvJCKouYi6c6yQlpqFC1RZfJWdfxlsPl+hNqnyd7us4mHjWaZnbeNpA0mj47mSkv5ijqUW7lPQ/kRlVXF6Kjlw5Myqe0G5OOnGjpNHT3OQXbPmxOQpknXRpeDKvOX0VKQplMFlZSl5/1AooBLw4i09470EZX0T1bvF/O+dCVVoLaCY3lNdfF7LUg7hvby+gV17T1q2hpNDTD2XMWuoPm9WE74X4lgdGUXtDQVegp6Vuw++2UTESqASal2uG+Gi4qnu3SV1VRVGapW3afbrVMfkGB69pIaqI6k8uS9D8VUVNUyj47VNtbVmw3I5k4pde/xW7n7pU9baugq6jZn0CYNoSktjHSfs9iP1BB1LEfRluor6WCqi1QjqKnLpaRiUIQkj+bzuNd8y8ordDXUj6lptY0jMEfGaCs03Au/PvgjVDsOuIYxWxqozNJMrXjktuhzq/H50LP2LhFP4zkUPZF1BfP3s4PxTLCDYGI8oAY7Aoz0vjPWbKWqn296QYkvbfQ6hxUwi7ffXnzco8rFq1F1PQHxz2mCmchdFxfdxOtj0SEkRwdaXcEiJimc8c8zwVVH4FAWDzzoaMnbAfsOtVcXVAtwKe+RWHGyTO/gy3VPN388POZUegMXmzAqRUg1GkZr+dQNaauRA1NJIlgIECTZLESwEsgKKS3E0hPQCkktRLUS2AppLcRXEnBi/egOBbji5QqZD4XaAvadyXkl5GvpO/PoH7jY1ojAPkFG4BEZ1pIqppI/JIDtcjDFvieCOg8OMnjeLkwlGTJg+vqetHfIngncepOi1sJoSKPWaOf7L9mvnNvuTJgDmyqO4GliciTkcYfG0B1AmSkwbX1TbmYdzrGGy5/r6BwzOhJyrjSatEP2H81PKKeMSuJmhzF3ZRzRODNoCIGxTsMeu96OYK2xOiLJ8RHDTI7vWhN1xOjI1WOph1V3LR0RWpN1xJOV5WwJ2OMzSkVsCVviUVVik3ZdHWFaE9ZEf5HdxnqVvXe6oSqPDRnqNWYtI7ca0qqPriSPiRUfNjKG8Mi0JpGPJS+TyibLGDIFvfdI5hHPJqePRR+W3jUBwXn8bY2FWn1Uh+AGiV2C25AriM4jpkP+zzfSye9DT4jah/GmKuWHSnaZQZz3Ad6SXeBn29j1Kd7SXcSbCT67MCDi+7AnGV/C7vjNobNdJBD5fKkcYmzg7gdJJSEEyxmaFX+2wuXGjzYyGVPFvxc/aE8lN6LayP5toYNTacz+DOLfljM0Up+Ktc/iNZKfinrN8jXSjxf4Wk4DEGa8sfINsfIUV2JuSiAOHJwJcEXgzSPRZoiwSvpZBGFmCZ0pcMVCZj86k+CKis8yOtPgig/OvnMmyhKJKUk4ROFKyhYomUY+lHTmyhKUPpDhikieYeLKmMhzsuDMEgfOwrX5q81QtcVmy1RYIFQVuTh/1JWRzyuZmT04vHrvScYbkS2bMuV00HrF48nX6a8nQZ8vfdjvjNn5VU+KviBllvog6c/3TvWkawpGD6+voD2JO8M2ZOzyWmZQr9ja4jfkznLdZtoP1q/wPOk7Yzbk1adhDgKvCB8YdBGIXRF0pRenr68+PlD4RNrmxsxGXb17IPEJ55Nlnx6/wnyg+b0oRD+Xfuaf13/8w8KPA9cHOp+YLnn+XPwZXGfy59Bf+e2HeA+Mz199pfgLcmbpD1KuqB9Yn4N/FW3OnB3cOuM/f3mR8Mvnn9U/qLlif+B+DnyRfM1/PATzjMXLl8TYTWQcSOuDTBj2kTGkmk2deG9aT7Pgz2q8XPnRaiy9trgS02pCK3ZVQ3ohvMnURkN7IbrJjHNs0FETZiHO5XOWJroj7/FIW92vSpjjYc+6jUqk41FQao4mTU8ATU6QRqqoRuK10fMywBUHewi6DhzNKKgytF+TUbr2uzUs9khw3U9rSOxhsbpp6/fYowN1F9bgGUNkdTvLxmxBsibktRYnIq6fMiZMaz+xJYx/LqqMHDd1WtJRm9ivu68MoDVIqgynNSZvsFTrtdTE1e5Da1BeKvvP7/oboNdHLCm5MmoP0Bmm1I8u7Z3AuZK2h+uOVxsuxmcsu1hz/us75wNq9avLuCdyrujtGeu9v0xu6x6XqW4AXrG8fXimFZq82r0L9S7WvF5feUfwjLCXdqyJvQJ4h7M/yzfIWjN7BfOOZhtNNqAvRZyQ3jB5BXWO6BnVNNBaU68ObBjY1bcsrZ7gNmd1jm4YnTUgLYVYw6wO833+9zeSH8N9xrsMvZZbTrhveFcHfQ3463OWJk/Qb6gfo54nXgz86ruXfF39cY1DNOKR5Th3MqV17NOodfawFlu/y2b3Y58H82Swb0d5IG8ksu+Me8BvxLdsV3lgbyS37Jx6IN5e6Gx8cdvNcjfbCHLbW3d32wi83e10t9sIud3zWJukxdsSzJ4U5hkj5hl5vHjxBvBHI+0GuoPFXAjp9e10pJLfGfB9RdrrvbPnC4jZLbgz5wuO2du5c+f7Ir+bcHfhzZTzowSEfMfiS8QfJg9kdn+XM2x2oaQnlr3dcI/Dl5Jy6eHNV7MF705asw1/P9yRvniupTeIftH/hOJLxR+VMzG5ZQZquFv2fscfkjM6uQO8hL8LeiLqStQfS7mQvit6YvLl7A7QH67ZVr+0umt64urK1J+022L/0XZi6gvfnVSz1XKR9OTqC9OdsNl/tn977nXv8+TbFc7fg7+LdBFyb6mHZPWtyRtXfxL/Zwxo8A7ajPYW0u+Tmot874ots18w/2jOzuQl+l3EE+kLk19Q94j+Ts0lrTf15sDmlh2o5W71Cbcrq3t0c+fsEukuxBtmc5h/u/3OtivEb4z/Zw5o8g74BP9C+hruN9790+u+5Yn7hXdz0G+LH5RzN/mE/kL9GvU68brlB+q+8/X1x98NcVci+pSU2kcq+SmehjKeyiKeDjOe0kQSoTBYqXlOwpKGNS5darxwXwm+rGhOypK2KW5F6rSnezjOW6l6TvCIwiWeS1q3sFqJvax9TviI8jreU9qnsEsJ704gGSU2QKkLJf6Hkki41HPhywzgPBxaKrAQnJIMVUpUSYcq+dMWNUJcsFRvjz4WYVSimGRBEeOMhkUmi146gWwimeSgdEIR5YzKIaRFunO+czyLbjphkgRzkaZSmQrZePK+hFORo0U2i355LJpEklJSowKXZnmyZaFWmZwWCW2yXJxcklyCXMpE7ETiRPxEcrIEUAIoBZQESqNLoEuhS0oXRRSZzJDOFM2YzOzNoM4kzajOzM+wzjTNuMw4HnoeQh+KHZIdmh6iHapZBDlnNCq16bYJtym3Sbdpt4m3qbfJt+lrkfIS8FLwkvDSVCUfFbHOaFlkNep5iniqeMqsEPDS2SRmx2YnZsdnJ7NJZhSZFZoVAQuBReiF6EUphSlF6oXqRYuFi0W0M2oWGVfBV8VXyVfNV9GNup7qnvKe+g8CDworhKeJfPGuku1FvDODM+QzJTNmM8AZ9JmUGfWZxRn2Gb1D7UPuQy+LnKvAq4KrhKuGq4iriquMq/arkKuSq5RGfS4C3ERESUlBSFQZe8J3hMZ5sKrmQujBDKLJ5gRY4dbTEixosiLK0zIs6LQi0tNSjWg2ItrTco3onD/IHUVhphWdP2WJok+rOiOviyJNK1996hTFn1bffdddKyIAKdoFG1YbGlp6QP4QAbbNwajw/hMUERmcaFxoxOe4D4H9HxhV3iP39sMyKkV+KujHYFSLRP69xEFR5tNgxPDn8FQquQ+zfWHbJIy6Yx9IPxenkkqJpqXS7oe25uuMIV+KBmkQUIkmaVDIoc3ni82Fc9VJ0KCVhCr3W2w7OwRzKGeSTqBJ93Fu6zhkc+jrENChoIcVbX+uk9EhokNNCRvtR92Wckj6pqVDXI26GLa37ekQ+E1xjcQWrSVUux/OIUOD0hbdLZS7X3fb1iHmm/oa+S/0ij6IbcGLWHeNSrTrz1Ea1Ath19sfL0rdZaw/xEREbb+7KHSX4qFlCxvfxryodJfj+b0OIzylb3Qb9aLcXbbj93qMzxnuwh2UG5/sItz6XC+q3eU76Pk+4Ifjfi65kzj51N6Pd1F3J+JNxYecE0Hfl7JNfdF0J3aCuhl+1nf7OedO8InC9xN/hH5fzTb7Rfud8BPly6fHfjAHBZxPkmlDKqZMKaSaQ/WVQ+WVw23WQ8WZpOyx2CPLjsStdWsitlTsCRmjtLvJjtStTWtittQtCaujnPXyE0ncQ7h7co5mrRFrqr/I3FK8hnj39BztWmPW1CcSnutJYXZzM+lDdmtx4goc+Vu7eQT45PAokOLhd1N1KNCHHVo15IYC9whBCh6pPDp4hDGJ4sMFe4wgDY9MHr1sAvlE8uHB0YQ9SpDKPaRHune+dzyPbjZhyhDznqZjmQ7ZZDJwyGnP0SObR786Fn0oyTGpQ4FPszrZalerVU6PhD5ZPk4+ST5BPmUydjJxMn4yOWUIOAQcAQ4DR9GH0Efezh73IvZMQKSgIpAJaA+ECkoCqYLmQaygJpALyPHe8x769/rSe9N7tHs1jyDvjA6lLt0u4S7lLuku7S7xLvUu+S59PVJ+An4KfhJ+mprk4z1WkJZHVoeer4iviq/MBgE/nV1iTmxOYk58TjL7cMae2a7ZHnAXuIe+i76Xspuyp76rvre4u7g=
*/