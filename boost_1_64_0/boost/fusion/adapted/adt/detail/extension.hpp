/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_DETAIL_EXTENSION_HPP
#define BOOST_FUSION_ADAPTED_ADT_DETAIL_EXTENSION_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/support/as_const.hpp>
#include <boost/fusion/adapted/struct/detail/extension.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        template <typename T, typename Dummy>
        struct get_identity
          : remove_const<typename remove_reference<T>::type>
        {};
    }

    namespace extension
    {
        // Overload as_const() to unwrap adt_attribute_proxy.
        template <typename T, int N, bool Const>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename adt_attribute_proxy<T, N, Const>::type as_const(const adt_attribute_proxy<T, N, Const>& proxy)
        {
            return proxy.get();
        }
    }
}}

#endif

/* extension.hpp
Z+JRbjEap8BzhfKRtIFMTSic4gPTZ19KcCNq+Q2vjWM0ru+G18YRWpnCeLkABBbmgc7lI2gjNJVqERqbzUZgNt5JoQBCAYFagOMwQbFnWuyDloxNzzYQRZ98IBqLQ4dCM5UUyghLR+2HsbHEHGr+mA8FRym3MpxeY800uI+UHjZEscOGKp5y4VhcoAlRgMatDDBsZUBBKwOJ2hNY0J69VLcOum+5lVxvDEf1TnHWOuQgNtarmPb7OLpLEJUaPwZrzV43Hb2oajWnrd+O8SNgVhBB5/uFx7astM3qA4sWrDJkzMFgnA7VdchTKdOyEqweWNyHV5kWl/VLIh6AjrMNA9MGpscYcl1WMVsp5x7FrCXixihswtBUki0DBbgIpoNejP5orYMhEQtggyIzChXPYM3pSaCYxWDH+Wht7vD0AZqUx7hZ4GLdWMXEOlSNMP2tYkNwqLs3qMq9hsdlSR6ETsGqXBNXMasFMmeR6gMsXRytJ2NawaDlDo6Feo8UCLRdMsaTaCIuHGoqD5hOAOAZRRQrBnppkewDi1lzX0XjODb7J0B5NQOtn5WEiEubt3uQG2aumJrpTC27lHx7QUDq7V5iAD7dbG0fyxCBVpAYjsFeGLcMT7rEVEmQfOuUAjsqJ1v141ZN+K0p1LUJChP+UMa4SCBE0z0cRbgfJNcna6gVBljCooeWZaO5wrBWO6RxMfi5AMUjeLdZzHs4eGw3hfjKx2wRpzzp9tfOmt2Lwy21HVMTIBZxPnxl5QCCxSNJ/GpRbKB86kg0njAiawDucXiQxeJlhMk8uD4JW8JsHvUAOnZG+KVTH2B7NMqDXQ+xp1UBY7AAR3sgvH6L0+CWRF423D9vw4SLwxq1yV3bDF2ctxg/g/bpnbsKOlpVAnXnW4Y0r/6C0odyMeSU4bKO9mTxNvuitY/CzXvxcL6nPDTgwr5iCTfTERcqG4OQUNExg1qYeMh4aAF4axtWydoAnfRro9K1URW1UXFtVFQbVVUbtUVtFNWmrAh+qGn9R/IaIEtS1pIQTlqG8izDl1q5ZgLKS4epEn6dw6igzFlUhHQtxlZFBCphw3308oBENog8j0NvGPmOOm+ShiAyiiDoBNjK0oHpo6tzR1ZNOgKQxiMRf4K2TGoL0+Y12xBEuhAK0obJ/BRBZN0IfW1qK9PkvhBemdfVtcQGGs8SyMeGlWHoJkfA92Sgm/rRkgmb7U5NoYlm908gaAvzjRJA0pkBr/JmYLnuzNJlfuTQQKQ8FGDXRVma2NZJWYLEj91UAJfqTjoq4KFH8jDSqu9efAQ1hXI8LFmC1lwUFY2VQMYNPQrSU1OScwOR8m6AQ/dGUIUSVEIJKlaCipSgEkoAli4hVoKKlKAqlKB8JaD+5a9jLsa/IESuBYTvLA1CdmrdpSbSdqp8O/W1A8qNbKsU1ER7TwRc9wnS+k8EqY7kS4miCkYedGUR54/whulsrQfvolRnAhAq3DXnzkCZ4/167WcMw7zdhwAOvPbWTmPGM5gAZaUz21oIwBCDpBud3hrW9OZ9KSB6ixwBaGOwoSOhiSbwW7xe6eSvgsxKJczNzNrJ3q6pCZD+FA3ACnlNIos+75Ao1qFUybRO0qfQthYwbWBoihtEpLa1wPlGHsphaXp5Gs2CmyIKcX0EHcmjIfIEgLMSic6Kkp2VSlj6Z2MYSRDWAjwRNR2xOBlvnsYbG9eoPkYaQHAhIRQnXV48tKSn5QGJJ+KqgbO2ePINiYhH+8SEbfYdAntkRKHHWMJPVT4cX683sP73YTPKxTie6rcCDM2OZYELFS+EFn3Gh7G9gTUcHvX5QqRlqMFLnWgVCk/j/RSMDuRnDve1EdYaa1wavCM=
*/