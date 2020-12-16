/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_TAG_OF_09112011_1842)
#define BOOST_FUSION_TAG_OF_09112011_1842

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <boost/fusion/support/tag_of_fwd.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;
    struct fusion_sequence_tag;

    namespace traits
    {
        template <typename... Elements>
        struct tag_of<std::tuple<Elements...>>
        {
            typedef std_tuple_tag type;
        };
    }
}}

namespace boost { namespace mpl
{
    template <typename>
    struct sequence_tag;

    template <typename... Elements>
    struct sequence_tag<std::tuple<Elements...>>
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <typename... Elements>
    struct sequence_tag<std::tuple<Elements...> const>
    {
        typedef fusion::fusion_sequence_tag type;
    };
}}

#endif

/* tag_of.hpp
0LMfVjzM1zmaobfX8X5EcVlXgz2Thg2WyuSu2uq8Ow39Y6J7YX2c9WCJEM7xFOb59ZOs42A7E3nxgaHRcWt7PgWuw/o0NLhpjvXDudCNi+aE640+45gf/3lWr2dzUvXis4r7GWN+fsDD5z+neGpN0wXgEGe7PZS+3mf1C319jvXTRdAnVNgXs0aLmrMqeZf0S1gnb+c0ucH++wL0ZmL916VgrUTZXibMm7O6HDoWW1I4X4Q2o+NAOFcwo51LXOFYv5J1WjDZmpZzja6CjmpL4V/ta1yvMC/0pYB1m6DI45eFFyvTUROZXcMMn0SL9YN9JgjO07URkznA68DWJvJ7fcEWVY4ZXGD2/VQO6bNl+RXWl85kzXJ5Ma9N/CpptHSTbL5Gf1P2ZB+k0nglJqfvG57eHddt/AYwOYKH9Ruht6bNLvCMniAf3hTpJqZ63fiQ0/lN4vR+4zlc+lv2lNh1F9/2dU5u1sna+Fb7nZ5c9kN9l2wwRdmcbDSxv+Bm0Yv4SLtFaTOnTPIeSKfRjo/K7ENnkX6r02l3hlvjfFuozz2U8nI79PgLKM7DBJcxIOs/EB3HZ+M8TNIpjEq9i/MwRfPWMP5YdMqcXKWOeVrhMtrBs3f6zGy6suvymf/E57rQeW9kwPGrhtjPfIaqxWX7c5/5lQM2d/Ww0fX6F74ND/Hhw7uFufPh7lFanvDVL30+W/vqXs0SvvqV5glf/VrzwFe/0Szw1X2a9fDVbyOb2Ff3axvrK7TZ3xGTtf8PuL9tPcZ+SdLT68gfBNNt7iFoaHM8FwutV1v5A3jYVv5Ierwm/RHorg1B/5PTET7y+mfS6Rcr2T1Kf+tt/dgbSbrb1k+2j5HGTqWGCdvHtd7okO0TStPnKT8Z6iZa+x3iqYINma2lZmy7MnFe8tMJ3kC4z8TMzYk8S6w8srh/5VhpxZi3zvyvAbN7AP7m664N/Z11zLtUhvuXlLw0/iPmLo3/jJlbp/4vj8n7499a5+SR/h9Pl7mJ5zyd69mMOr9pg40ML/fblyuFtSG08pDzN+nPE536TlvezxfdpX8jpeXK9gXQ0VbIdmPW9EuXbDeBXuf1cWS7qdP8NUKbWd3U0MFFrG0OTZfHFqwF/Qb76oXMUi9Z6le27M3d/oWt2Ea/hEl/kdL1eOPFTkengLRsDT1+ifJz2zCPzhl7idN9+21Zl5co4t9O6Xp+4aXQ4xcp+3H7iFOlomd3YJZ6kdKzLwu4nq/dMWCoDsR28hk6bWYvD5nxsSknSs/OAXOJQV53CTiXq3kaYe8acKqNeHa3FCtqfJfzunvA9TnEeyimz9R8hdbz2Pd7Bny28v1eHot9v3fAte/3iZj4ft+Aad+/MmDa9/t5LPb9/h6PfX9AwLXvD/RY7PuDAg7f03vvYGauv5olf6PdcB8yG7o+u75Pa+oc8Tms+wMCPHOIZUH7n2v1oP0f6vR0+z/M8qD9z2M9OiPpcNG9/B3BOrsVtkdCE3ey7aucflpmbV/NWnQO0Gug63OAXssaioGfP4o1NYhgvV/r7Gny8XytSwkQGyC21OztMuchD1Za5pWW51Mc3iCY2Y7MmyjtnB7rOCOIP79ya+I0L2BOk0c2zwuh1fPW+LriQFvYLoKux01D0PQ76Ghok5mLz7FjLJtqjVen7FGH2JfJjJewQFsCbTprT9pzHYZZc3V7Kf9Nx/NygjmuEeh5Fuf7WGYoP873qNFKA4PuF/qhfRxOmfXg1zE/M8asLKMJ1pdBl9EE68u1Tjlg/ThPz539CuhulAA/rgx100rc+ZSKoTLy/kyr0wNse4KnybnBJ5IethLs2VTsNOS3YrXgrP6TSB/pH+03tbY0WtZ3l1Q=
*/