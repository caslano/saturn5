#ifndef BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/is_whitespace_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_whitespace : is_whitespace_c<C::type::value> {};

        template <>
        struct is_whitespace<boost::mpl::na>
        {
          typedef is_whitespace type;
          
          template <class C = boost::mpl::na>
          struct apply : is_whitespace<C> {};
        };
      }
    }
  }
}

#endif


/* is_whitespace.hpp
GzxXZdnpmN0pli0AL8gyill2hjbdctkzTnaRwKYLDotdgr55pO/lOvJrkLTCCNOxjUwkwB8nQglxMUmm+snQCILk+cEVoHeRTC9DhZqsAD36CNouQxXegSrImzs6UR30V3BJDlbsQjw1Cq2wHL1DNxyBAquyMqXLwV0MTAvcBMFb9Q38+RwWeOJjgR1dQ88lBPNY0WFxP7TGo9dJ4XK5MVDZKJAE7iJbiedrCp6dWCEEbTwZTLP6+yH/bywTykKu8BW1wqeVCutQQRDdj1FTW8fmcHfMuxth/nKDWFltmDk7eL6C9z110p8uUQykLmw0y4VwmyY1+5LJ8qTLZIp6O5rDHV9hbl78VLSQyJH6irnf31PBHWk/RBqIg4mH2pTKp0EdJ+snBx5SCQ3eLqjswBwglX83C9NZiL8+ZTDj30Im6plCx0bC3ab6GZHwDlP9lBhk6GuUpPV5cA1QxKrwNxEJT0YG5V5VQTl8bqqZE6HHhKkCjlWQosGK7YBpDg9iN9x0cz7HkfY/GflYJiPLFRJrSA012Oc4K0TobM9NduGj6kzkQjzRtcCtea9gdy+HulZaOFWZGOj8M6innxs/XyhjfhP5nF/+3qgfC7vXdNMluBIwfKqUj9VPlaayAM+uhs2SWxWMPBFkt+ALoE3SW8Gx6E083BzuQZ/PupFk7wLhPfFj8Vvoku5q38CNkwMvZTJghow0UcdBpWNuAIOCHUaiMMX6jqFksjk8QIbeNDmwLxPJq2fLSAogFtCxKMN+4RTh2vlNKYtskY7/b49Cav8HQRikax96zi5L++CRga00BXmV45RaMQ9SMngayjineFBMGRxaoMrg5ZjxGK5W2A1UCTI6oMapV2qXPYh3aCvz1axVgol6RHCm0hoE9xOniNaArCR4nJxNYf1VOfv9bEQ0/TLZp+k74btGs9QT0oWfUPUDOyp2tLXkizPljqBAJZULl6eIn5uicnBOivh5cja7unfOeyE+tf9Zopz90L5tRc7wwZoU6GdT3Ms4aqXPXagfL9gYk1lMGfAZDFb7PHWwzsk2WEDHbBELD870gwGq8dMXnAFESk8L5S69H9tOsz9az9ft75wy4z+dGhmcaT9xRdrIlILncpco4jgF3zhL7dUccBwmSMo6GYBRIJ3kY7mb92sWoKoy1847WelE/3vpBOk/jfT/YrH+vK7d24FRgwrYrTkXHNJLH6dFsDuRi27h/0h4tzyaZ5hhbPn2QAWil9WwezgE0GDhLp70OVDK0736XHG6Nzm1hrrqpF8XCOJb2gDI2EeoV+z+oBMi4U5u1qBwLdXejhuvDGyndNz0MDvdUStdQ1aQlwKwviywQy0GO/fI7PwGzloo1qMsalfLiZIRv2MrBQa4gql+sFOCzraTKBiGoK+LDg/mLXLKmW74MeR8T/P267BdqQv0EJ23A7mdtdK3SokPliVOwc/q4W7DRjezGe21L7CVsG9gHTeh2ETjFRe1TlO3nsI5fPeSD8M5jPHHaHJ2/W6ZGDgQMHx+nCzs/0Wc3xJehWGgNxu78ORUwRP/gfv8rxtP/NevsyxTjgsnN2pc2oPOcE78BRpbwpxwPV2bjLxzKb1akuqDTL+lIqpMV6GLIu9UNRUKywG/7JG3ZwNdEy2rF5QdHhG7nvaYI6/Nvna7xDBTs3r3AvlORyQ+e8Wuq6zc9fGagz7XwVztNgGQFLUudHdB/SsoLALY5ohIs1d0OJT2cuRMS+sScxeMMuh8Z1MunmYQ9ieAKGC5KbIQwKo0k5fWTJfSjDVbM2PSmtmt5DqyYc1Pw7qHQStVha473zRpxDjVau/Mdt35CrK2iPwOp9ryYJXr7ueQpWCENUIuuSM=
*/