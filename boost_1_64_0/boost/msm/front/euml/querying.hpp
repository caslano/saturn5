// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_QUERYING_H
#define BOOST_MSM_FRONT_EUML_QUERYING_H

#include <algorithm>
#include <boost/msm/front/euml/common.hpp>

namespace boost { namespace msm { namespace front { namespace euml
{

BOOST_MSM_EUML_FUNCTION(Find_ , std::find , find_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(FindIf_ , std::find_if , find_if_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(LowerBound_ , std::lower_bound , lower_bound_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(UpperBound_ , std::upper_bound , upper_bound_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(BinarySearch_ , std::binary_search , binary_search_ , bool , bool )
BOOST_MSM_EUML_FUNCTION(MinElement_ , std::min_element , min_element_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(MaxElement_ , std::max_element , max_element_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(AdjacentFind_ , std::adjacent_find , adjacent_find_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(FindEnd_ , std::find_end , find_end_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(FindFirstOf_ , std::find_first_of , find_first_of_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(Equal_ , std::equal , equal_ , bool , bool )
BOOST_MSM_EUML_FUNCTION(Search_ , std::search , search_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(Includes_ , std::includes , includes_ , bool , bool )
BOOST_MSM_EUML_FUNCTION(LexicographicalCompare_ , std::lexicographical_compare , lexicographical_compare_ , bool , bool )
BOOST_MSM_EUML_FUNCTION(Count_ , std::count , count_ , RESULT_TYPE_DIFF_TYPE_ITER_TRAITS_PARAM1 , RESULT_TYPE2_DIFF_TYPE_ITER_TRAITS_PARAM1 )
BOOST_MSM_EUML_FUNCTION(CountIf_ , std::count_if , count_if_ , RESULT_TYPE_DIFF_TYPE_ITER_TRAITS_PARAM1 , RESULT_TYPE2_DIFF_TYPE_ITER_TRAITS_PARAM1 )
BOOST_MSM_EUML_FUNCTION(Distance_ , std::distance , distance_ , RESULT_TYPE_DIFF_TYPE_ITER_TRAITS_PARAM1 , RESULT_TYPE2_DIFF_TYPE_ITER_TRAITS_PARAM1 )
BOOST_MSM_EUML_FUNCTION(EqualRange_ , std::equal_range , equal_range_ , RESULT_TYPE_PAIR_REMOVE_REF_PARAM1 , RESULT_TYPE2_PAIR_REMOVE_REF_PARAM1 )
BOOST_MSM_EUML_FUNCTION(Mismatch_ , std::mismatch , mismatch_ , RESULT_TYPE_PAIR_REMOVE_REF_PARAM1 , RESULT_TYPE2_PAIR_REMOVE_REF_PARAM1 )


}}}}

#endif //BOOST_MSM_FRONT_EUML_QUERYING_H

/* querying.hpp
gzQN/WbTw+UYs4SdpEuhPOQnZWR2dtRiNybqAyrnN9V0jmZ4oQqbSI6Vc1tgi6oNrqnYZ/leUOBlowNxh6+WsDEj+SLHk5yyQCHDMKAiskWhLOIE7m+6EPXaxSR5wR1vayjl9ItOG09LvK+qjh1W5fyD1ldR0/M7eIhySAjiZ/q9/y6OpznWhAO2KOwUelv2UdD+mJpzh3I+9WN6ObMElyDf6QGeCHBRYQ++Wh0jUaeI250i4uPvLAcXz632WRVbOKmXRh28LDiBEBmP+wN+mqRuaHhV/RZVXojoIKjE1SzolNKWMt4wk+3yQzFdBZEWzVpl3K2oaXmYql7YdIvcrU9rCmHodMSakH1xlHehd77akIEnvg8RZOTIXUm+GDxLv9N+6tWG7LVohXmUdRz3Um+4wRTPxcX5GHUQlf+bGq/v+JnnF7A45K2+hZ1CrHmL1QImCCIlkh282thzWKPmbsYu73wNVB8QUBrRomrKarkWto09B/fWVhA0ndZ4zuSd20qCpTDSWFVPV+c7NR2vcPxW4babTayJ+s2TqlkmRt1NA4C9D1dlO7etywnhwhPPjLhosvPWYFrebti+cYzd4su6v3o8fWVvigDWKJ/ToHOUms4JrwgjCIRis+Wpzy5W6/x7t/W3Fijf47UEAgZwLGXYX7j7LJQC66Xs8mmzGi/b+liDWlAeY7yB3+BdYo7v1GHTr/r7utYGiYMrXt7x81aZRpkOPY9kaF7WFtTEkijHz13b+viJOp3cDdKC0qP+ogQpOV7UFYwhOSeeeFmvIx79vShxfT6f2AGvnJxrZd8/S1///Mv6W0Ac+B7mRVKWJaQ3pKwaNh4vCH6ghrpcjZXzRlpB0Pagu8DbCcMszcZmmviaVwm5dKa7rK9ZmOEt7IsFpeP1RqdOzJloezobqNJQLT0ae1cva3ssmxKxF8Zlcstb/C0XTSy45DvPF3W+ELL1AucUBxmAM57NtgZThXGpOov3n63sA88MghQmXZDBVuWaVbhravpHm34cZnnLd1KhVkB76XWtPXKnlbtNzGw8PFYPa7agw5hQLp0pL+v7Mt47kLGbyrWrvBDgHDie1ifVcKtxt+81hk1Wjq0pjH1V9kFLlSEzOqzy+lhXcPpqRegU2kvYOXKRr3xs4GpraLnPlDIjkj++xpBjZzgRJgE/cJT14pNhvl1ea7BMDdmLDj/vUdVkem/W0sObttdJPC+LHUpmZux3ViG199ava23FhEtey3exSFdjueBjeeemazhkr/ri0t5V3p/EzQmk0SNhc/WOBzDfpQxTHl5wxe+WL5szABj9naDvvUWjTyFSGY8AeAzocyaDu0L0jeGFbin277KTBktDYBpnCcPp7Lld0O+/H+Us6fymJW6B/YZC32vRWRty+ntQxl+Vbz+8wTf7OCSuoYT478Ei/30lv0gYgoOHie/7y+/scGnTDpS0fi3tYElj45+IZVne9wAQ30B5IWEhBxV1+QDoC5Lel3SZ9t6SDkF3tzeYsRcBwftB8N6YsHqyZAWNNYOgfwh051UVfTBaV+gPY7YBQtf4zLEus9zrpgECN/ic9gXQSr1kpoUa+8yAvdloGDTS9mRUrsf5eaKVGrDxSpR2oTqTsSgOgbCp/9IDuM19pV/64CrN4DQPNyDSA7asvwxYwvP4FtcDNPyf6/Y216WeoXA5CrtFP7D0s79blZf5LxU+llkdf0D1wPuN1C0ry/Qr0Arye8rT+TW+iXxStyhIN/Y3ZTnIx9Pyi5orp4NA11//U4nhfRBzW0ZV37Ksz185RnQXNGRFb1FKom/+wXHCT6XeJo0H1qeh6QALvwAKKESBy++7wc/fSxEHw+/CaXJW2rI=
*/