// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_THOMAS_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_THOMAS_HPP


#include <boost/geometry/strategies/geographic/side.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace side
{

/*!
\brief Check at which side of a segment a point lies
         left of segment (> 0), right of segment (< 0), on segment (0)
\ingroup strategies
\tparam Spheroid Reference model of coordinate system.
\tparam CalculationType \tparam_calculation
 */
template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class thomas
    : public side::geographic<strategy::thomas, Spheroid, CalculationType>
{
    typedef side::geographic<strategy::thomas, Spheroid, CalculationType> base_t;

public:
    thomas()
    {}

    explicit thomas(Spheroid const& model)
        : base_t(model)
    {}
};

}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_THOMAS_HPP

/* side_thomas.hpp
q1P/wT6BMewfjIaY2Lvuv2qzR+plujZxNUSG3PP+zLzcq6jdwpXdrHaMM6rdQti69Y5x1u09L8r0fCfz+GuZx7ml83hAP8sp+pvHab1p6K72ZwimxrfVNzLcfA7jeodl4veAaeRdZBo6yDREJ2rTMDww3icmyhgVHBXx7+zzCqQOnlKHR8z7XYs6hEf+O3Uwby9JcsZqlDpEmZdlaR2Uy28eqv9z24ty7f6oEx1DzdfmUeooaGEba7xtOTk5yGfyS/12mev3mFY/n5jw2Rz3hxkS/gfbtHm+HXfQ3yenz9PqZV5w/1idlPnWg37ytXse0TIKdc5ZbaNj65hGECL18zfXL0mr3xgD+8GYIZGhUcqR638w78ztuYvr6O+js+dodSt7FPkH17+77a/jH9TfLgtKz4fGG2LCQxP+xWP+TalDR6lDO/Pyu70O/8Ix31yHtLr6+4aA+bfVYXhUyD+5/ij37noq81vbP8wOTTCt4lbruPdDpsLnS/3iSW9luDWm+nFZIncEZQfzN+vYycn6GtkNvdRusXSkm/W9pxDztXw7qa9bPfk8XirXBG8qI2X4pBS1viFRyqsFMYa/dKysZ3Ws7NcnVN2kTd0DLLpHs7Ko7X/pHqZtA7PVxSijl3VFu+7h0qp0erc4qtOrDGa9vsq0bSLOZB3pr+yr1qrTNjM80n9mYLxph/VPnw/6aNfyQVFxnA/Vt9q+uYvnz/TFyvK3Oi/g9CQsKqT039brV55j6fpVR9avj+mWsk6dJm3nGxoTNdM/9s9dl1iv71UdBjpZFCj1YZenXYM2M01LmfubyvtuQxg2xaDUXRvQan/rJhfkjqSWTMss/vB40vRuywx/304e3fxH9Bk+wF+ZW5FxEZxt3Ol8w6XMOzrHZRzuMp4WZDTbp4/OOKKjotV7v/cyDvO6+DB/sN7NMK/TXfGwOg+VkpR2fdbLLuRhUymLpT4LZN+QIvWxeCDgHxgRETXHEGK6d3HP93pL76O7afsGo9qPnXYvIzg0osz9DSPdrOvqXN80kmKp6/dkKOV5rS9b14ioqBlx0f/E9kNp2v1yrf63rW/h6v06xw2mexrDnayX+Zn6Za9rRir7sw1l6x07Izxa7m3/rWPVR+r+J1qpvFq36hvVcfEulenvfqV/Wx/LGphG8Ly8T/gMGUX5LpvMdWX/VHqk+Ft1bGGal0ERZbZ35RYQ668sB/ZB0o2bQ+b9utY9KjIqNFSdpl2b9KcpWr5w+kPiIt8jNYZx26dq08Ttae3Y95fW7/qyPsRpdZVHAHIM8cCmpvqqozHdwJR5cdu01JP733Gm+65SjvW24NvQVCFnJqABOuI4ZTltLjNNcsFgmi7fO02X1TGQmT2TblbHv9L5H40V1frFxcZoy6/sMh2ssx/oWrrdyPphNf1ae2Cnirbe8fvz77Dpt9e11X74z7/Dpv+uoK13+f58O2T9dxptvbv4599J0293beudyX/u3Tn9dxptt3PWf/fSdvvnmep0ZV+e2GRzwP7qS2ucLV/vxt7nbLWv/vPtt/Xf4bTd7vottT5FeSurNHh07pHGf9i1b35szOd//t1X0+cgy7N3bCXPlC0/B7lzRdPn03bBJtgV3bAbMjzPobTn5TxHNw1fT32XUD63nP7qYGVsgFWwJVbFXlgNh2J19McaGIc1cQPWwn3ogHlYBz/AB/ETfAgL0BG/Ryf8DR9GZX9WH5thA+yNDXECNsJp6IIR2ARN378hz88xW+aH5fdvuMr0NMdG2FKmww0DsRUmYmtcj+6oPpdH0/yW59/YUWd+35T277ewFf6B7bCcDJ9UTp5nw2EZvhYaZfgeynRjT3TBXrK8emN/9EJv7IM=
*/