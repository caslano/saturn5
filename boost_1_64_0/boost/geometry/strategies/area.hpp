// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AREA_HPP
#define BOOST_GEOMETRY_STRATEGIES_AREA_HPP


#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace area
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// If user specified a CalculationType, use that type, whatever it is
//   and whatever the Geometry is.
// Else, use Geometry's coordinate-type promoted to double if needed.
template
<
    typename Geometry,
    typename CalculationType
>
struct result_type
{
    typedef CalculationType type;
};

template
<
    typename Geometry
>
struct result_type<Geometry, void>
    : select_most_precise
        <
            typename coordinate_type<Geometry>::type,
            double
        >
{};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL
    

namespace services
{

/*!
    \brief Traits class binding a default area strategy to a coordinate system
    \ingroup area
    \tparam Tag tag of coordinate system
*/
template <typename Tag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_COORDINATE_SYSTEM
            , (types<Tag>)
        );
};


} // namespace services

}} // namespace strategy::area


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_AREA_HPP

/* area.hpp
ImJfJmVzpxJlh/ik+Xr9hTirF81hOMbMdw7DCRKcahPOkQznba+EMwFrbGlJ8/k8kjovYq8hM6aaCzEXNBcymtdvoY5votl4NqG5yguhRTRvC8XAY1OF84OQV4rUH50nXCTx5wHA3hE8iuv48Lq8OrQCrO+BtIXTHLNw9MjQDqMI38fPOdIhUooGr2cixxKRi00ihwORbU/ishmhxYrYCVvYtJEMrPJZY14GtIdAwwVWtaBBvW68hClyskmYGMvkJLgRwrsCG5Bxop4GI+NdUg4xhsPgrHEcfMwcSXGaTRacowOUQxneZxvpfKAEGV9FmY3UwQQk/+wmSm4klt22qQZufZMnLsNAN+b9F3tHAh5lcd1/d5NsQsKGGCBolAUCRkEIR2miQTdtqotGjGfxbKqoqaBGs4GoHIkhNDFQqUeL1ioqKt5oPRakCh4QqFWsWq29aLV241rFVivByvYdM/PP7P5JNkjtxX5f8v//HG/evHlzvXnzHtxl2Op/IrNjW7QQskLyiUZy1khMzjDdghzvLVOFTcTCzNy/wdyoLwucPk8F91z+Lcuo/Ekqaa9lX2KXPUmUPcn/BPwjbAYIbDBkokkMOjQzG0NJgkrqj1OtEGK6klynElRWs4F3JTvkWwQzmgkkowS0k2b8pDJbbGViE9EKlnoCq0Vvpxskbbx4Te5bW5ltF3yPplSTbcMzLT7zP8WiOXAb99wTIS0vRX/6TVqKnsLybJ5VfnAtzSqd+2xY/lt+jvKrSzpo9tPESZ+0sDt1TZwU5JhYM63/pibIjy7gTc6pS5FPzkSh1UrFJ1Wn0Rh8Ix9l2aY87jhbDO20lWMebW+bieMxj/VjEfJFDPmzDoQMcTrkv55KkI+wVVeWl3rUO4GKvnk2DvQLBhuBB1BgWNZigqjFpVzWtVRWvVmLJVzWy6biCqS7PJPY/gzIBOBLLTwNPcVCABxRQRFceAkW/u5plqYNQys/zKWgips7tIwvJk9CjNbOa3iCM9D68BRa2R3BUq8Lm7Ajc64rOdezlKvSzLWWc6V9uc5GU/hprEnyjVfbiDXlWZx+AlJtL8uIF26Px7WFAgvpB7DxhafbFeXmKxo8fjLMul/38q5uprr/eQYxeHgCXoOUR8Uq8sccmacC3m/lVRQpfcnOsB+XGqJSbzNLPQpL/TmtOej8g/P7lwTF9jLI4a81qQ4YFFjUcMxFC6kDGgUWcoFvtGGB3zULfOkkKPAsjyYwqSXNYgIJygBzYBRnYwja9bZRDHAJAcwxAS5AgAP4KiEPCmKSKgP4JiEOYTBHOeE1FcE8L3Y81TxhPL0yrtSvDuO8njaHptt1IuSFCJsPuh7cLaUkmQTEf+1ryr6pOjOeLBUDySYfF3DHd7GANWYBN2EBB0MBsTMlCN0N2NGJgW7BAoGjGOjxBHSzCbQSgEoEurbqljFNjaFwAd3xpahofqswUneTJVxUmiZMtzbvInEeNF6la1FQIda2wcJV/2KKLUHUjmfUHl2CqC0xUbu3GuqLZw0IxlpI6U/k9FdDelIZ15JfWa3VBLchgDDR/mI4b8RV+4GnJV+AV4Q/nQEfQoh8aiISQEQeki2XLO8cAlzDRf0CTg4lFeyBdIVTVk7U0Y4kgc1uYhIapX96okU7dzKGCQohSUB4dlqdsBWku5Mx8yCfG+bSK3bF1ceKRfBBp36nQjlQ3IwTZT2u+TFfitlne/Nf8TO2+iHsEs1XJ84ola7EjX613ODXWGTx3+Oivej91NdwIBaaQx/Mj8fpUrN/MZ/HscVIbHYWJDbSKJ7Vsp7CLb5UfZuH+b9FTcwLbP4/Hvh/5yCeC+oUoPOvtAfGuzj7e1dj9n+Y2f8=
*/