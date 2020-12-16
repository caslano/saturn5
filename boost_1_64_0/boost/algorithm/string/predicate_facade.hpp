//  Boost string_algo library predicate_facade.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_PREDICATE_FACADE_HPP
#define BOOST_STRING_PREDICATE_FACADE_HPP

#include <boost/algorithm/string/config.hpp>

/*
 \file boost/algorith/string/predicate_facade.hpp
 This file contains predicate_facade definition. This template class is used
 to identify classification predicates, so they can be combined using
 composition operators.
*/

namespace boost {
    namespace algorithm {

//  predicate facade ------------------------------------------------------//

        //! Predicate facade
        /*!
            This class allows to recognize classification
            predicates, so that they can be combined using
            composition operators.
            Every classification predicate must be derived from this class.
        */
        template<typename Derived>
        struct predicate_facade {};

    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_CLASSIFICATION_DETAIL_HPP

/* predicate_facade.hpp
mnXWjjfPXJBjVtAkX2rve4fL3dVII8U9061IH63ENtsTkWRrxqsOtcL2ndNp299X7JZJv6hzxHjwKOWlGlWyCw6uMFDwnM/0Sx3MZKYMWQPFzB5UA1bf1cfV8nAxpVCmxCfMv16V9GZp8Ef81vXHfzd9+0al6wP58ELekfa2rWgrsc/MU+yEYpLQt+2Eepm7swkdEVNSo/Yea973dxKRpjWEHK1KcQeX4nqra83LZmkdYxMIS6UlxCQTif+ZgBkTFf/z4tk1LroMoSBkjHDxdXq9zZVql1epvmOBp+rSoDG82FoSHUVohPO84FSezR3odXP4p9wzRkn/eWgz95974d1eCUbk31U6omB2VTwuVXG+z6oKp9nukt2i729tI8Z84bV/yQ912FUVGd5HbsLk5YAA+8k3jz1BBJ/aa3HzMGmdI9kTXaXVOke4uJddPf9QtStkFMu/dJZ/35pfqATiig1cnzrqjC+dvAT9EMjQq8BZok8cL62kI3HKp7/YLokxsoeJJem5LJGOI4U5Dc5sXJchqnxHXXrVqSIh3zeZQ/oJh5w/wJaQbSKh/yQN/KrJDbwGUcsrD+GpOgiEBZJQj0ev31mXBnlQdajPPmNz2M42nnn/lDcUNrRM+upE5AHLy5mHi37P3u/AakE6or0VGi1q4iW0gHIfME9X555IZEbtbVEzzfMzuasNTFfniRqgHpHgXNtT1CwVf7qKf50VX5jhejNf4rej/tBDLi/f0ZBedYhKYwZgVF90kNk9/wOX+6Z62XIEWN9PpC4fFli2+6Yr8GZOR0dJct6XrrK9JTVb3bwHxpeWHyIGbeab/0eHSOep2XLGPWQBVmoCWKsAXguwSgHiCnC4BThOAZ5UAIcFOEEB3ApgpinAEyrzHS4BLLUAjyrAWwowRwFkG+cJZp0Kf4AKRzZw8cB5ifm0AsxOBRxh3smAysmdqRSbMyVsXBKiZv5EAkeoga6Phzl/MJS/sdDhiagroYWi3t1TvwmtUo5onprNkXohOH9KX97pNpAHyEMQr1jFOy2f2psOMdZ/xaPg1/fr9GdGByHmTuTLw3vLemkCvYk63GCIyOjLstnfaEGI2qlP4/FxtN/wLOHUtSwr82KBeeDTfmZbuhpUJ9J5ABmN382T0bhsflXqQlzBWTRyPI0W3GPOSY1o6TCvQ4dJN41Mbs8TceyVM183VDJ/jzIfXcW7NIdfa05JTYMvOPEZL7PTAB2t7JkaTE3Xy+lWeZFu5YlIN6zS3caFqpLON808HOnyxR9JiSMJuC6RW3TfKui8utXnlK2no96R/j4I337cGwJpdrla8D3r3Tb7OHXIQHjIkIQ4DzsHXmk1j3yrzd7YfQvt3d/RUOyeXatOWG/exLn8kha/MKvWw++76Dz4KoL5jpW7fR/ilFHmJX5U37HYWVpcQTb/cokr27Jihc/9wMWzpPY1bYlW2p1j9lUIJzuk+vKmeOC/qZjdq36ryJz+PihDhPHHqumZm7veB20JOT7Dqf2xJ20qtQ45vw6PWKch1SEd7lvH8KByP3tw4BMibyiV83Vo/EPJ74R7dlwdDozJqRMRAZp5LR9QljBsUaohQujuWfb/drfisVPkkLouu4LyeFdQTpIflXuGkB+Vi8yhaWrxsuVE2vZdlbr95Kohyhfe02YBEFWm5gc91cmRwsh4l9x+YxoDrITec0gavfBsjfIVf5AcSu16/RDxYjnQ8rz2orqmnk9BG4nwB47KIebgD8R6cJmLZwL2maOhqlQtpya6uHEaX0KnreF3S5/rd3Cb/uUMa6oeW60MUXZKw62UWtWJlYFq0o0aTSvhNfxziCEHhnhJFwpNPrySBMWmcgimGYI=
*/