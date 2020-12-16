/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_FACADE_09252006_1044)
#define FUSION_SEQUENCE_FACADE_09252006_1044

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct sequence_facade_tag;

    template <typename Derived, typename Category, typename IsView = mpl::false_>
    struct sequence_facade : sequence_base<Derived>
    {
        typedef fusion_sequence_tag tag;
        typedef sequence_facade_tag fusion_tag;
        typedef Derived derived_type;
        typedef Category category;
        typedef IsView is_view;
        typedef mpl::false_ is_segmented;
    };
}}

#endif

/* sequence_facade.hpp
Ot9v4ywtsgB7vLj8VNWa40djsLtemztB2El8N3TEfUyIf3L2UNIsOfdUvW9d5+dz5mVpL+t4DjpN5LBDlzXW29rZx2QC30vjXidKndFYJIHB7lDljYMIiFk8U809qsb+EhszHH4J1gmeCw366QCDVZqgy5E7vbF1GqLk4OxI83GN8Y/32izK4zSKdTlcBJV8nG6ruTPie2WQYfX57YzobRbUlBmEat8Z8bYEQRD12oGvy9j+T22h+XNqxOee306iNiQfB5TVOOyKMWTjodqxy2hxTMPHMvU8l9PScLAyaC6M+BwUoSzw5uk7O+PnjrdeMBZ7Pe4PY9mJdN5cGvF9N857vTiII9DRtBN327Nb26PZ+iZm5Gitvu6+x9uO+d/2sxS/sDImcjsqiddCNQdY/7eddrcdedjEGC3vfmJG8EB793P4PSDxu3EO2eUFo/GNh/mBsaru5QdNmiNx0E68rBc54mhUTdx+lJonz+FrzYuKdtvvQNYUZ8MWpI/jR4OsAzGuJCV50THpEqcL+yjczuS1VGzM8nqi9sOC1VNA5s57sZe7ppLBuCJNxU7I92jdJ7u8T3pFigtWkat7oXksrIbqPKrVH6aQHYs4dBK5FDGFsKXtzCY7M84Jb/clXnc3TjM/7lWaoSpjZoX/FHUemfiY+jDbaHfypFNRYOoLEuMOWg7oVFwKy+vwbHuw2qxj4v3fKQLsVKkrGREbdElBvh3hlnij3xxuwkqsiqMgz/n93IYMKRNdBZtwmMg86aryPlKWh+syKKpcOLK93F4sGUxngWgSQDvK9qy1R+OkuPeO2udmw5Wtp+IE9GCVTjZqkYGngCtbREE2VgdaGq+ctm4lVnmVWPVUITOrMg/WcU8MkTBxqnDJ7m2pjucP0ditc1DJEX+7dRzoGCIco2XsIsAU3qSOVxnSPV/iUZ3rDXjCGQZ1Es6pOk5Q7qEChXBaFu+VpGfa9RV1HK+UwAX7uv/n9IFAMstyrH6AUCGQnor8xeqOb/ENObBQcutTqawDNzHwsApzCBnLYheAvlThXG9xHG9jazqskIZqffyZ45TVecaqjmWpCr9VqzfEbcLAl+h6D9pfw/d3JhslpiZSc4rqWKzXsT1sQp+pvfkgxxfTwUZHH07wEcOfUR8yG8vB6vasP9o63RfSl/bre7BYv+JI6OstGzdz8su9geBlYE+cUNrn8w4ahm4SMB3jw63bAgm8SsFOtplJ5U/WWa4MTrc9kRrOyBuYVvDpcHUHB6JMId1fxU49whBskd78OVzPGnSiOCqgbzx+BH8OV/8XUup0unH8MY88fgT/LZ05frjibopf+quYu12SmZ7LZYbCjzq4K5X6S7ozkN7u6Gyr3LfDqbTjJLknYuVAP9T2srxIYipHKt+ohDVZAvYpdV6uszJwwMLULcv8UJdhHiCsKPvsq7ULQliQZbFnlYVjo6ldqpwPPpfLpW3Xz72sa/D0XHqwsBnSd7Sv1/oHR2gA+zomc0BNosRjUueQfF2jj5MoirxOx6T3G+jVebF3w7TJzYsoTfIwdAS3G7vyLvJwtc5N3GO4hBR+D6oOISSvigN6SRKosu/IyoZkIp4remXZOxKVdD4HNrgcE3faXoFuGIywnbsbZ83yaY5u8DFI09Bvtz0IbhChhEhZKowg25fpkoVYIaQHGgPi0zfLOZxBexq2UZzgU72/FKQDN3Ef5XtBAa1bD6K4b3Ko777FBr9DF2AyDANiUewIJYsTxA7pQw1hs0my7Dve2jL49IteF2rPaqzUwI4Un7tsrKK25/egJHVIQPczLpO+coOvsTaiUEVhr+B9uQZG17Z4d9p83upjnM8swaOT7wyAnqj+VLg=
*/