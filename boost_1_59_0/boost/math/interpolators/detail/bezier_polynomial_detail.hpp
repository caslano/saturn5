// Copyright Nick Thompson, 2021
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_BEZIER_POLYNOMIAL_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_BEZIER_POLYNOMIAL_DETAIL_HPP

#include <stdexcept>
#include <iostream>
#include <string>
#include <limits>

namespace boost::math::interpolators::detail {


template <class RandomAccessContainer>
static inline RandomAccessContainer& get_bezier_storage()
{
    static thread_local RandomAccessContainer the_storage;
    return the_storage;
}


template <class RandomAccessContainer>
class bezier_polynomial_imp
{
public:
    using Point = typename RandomAccessContainer::value_type;
    using Real = typename Point::value_type;
    using Z = typename RandomAccessContainer::size_type;

    bezier_polynomial_imp(RandomAccessContainer && control_points)
    {
        using std::to_string;
        if (control_points.size() < 2) {
            std::string err = std::string(__FILE__) + ":" + to_string(__LINE__)
               + " At least two points are required to form a Bezier curve. Only " + to_string(control_points.size())  + " points have been provided.";
            throw std::logic_error(err);
        }
        Z dimension = control_points[0].size();
        for (Z i = 0; i < control_points.size(); ++i) {
            if (control_points[i].size() != dimension) {
                std::string err = std::string(__FILE__) + ":" + to_string(__LINE__)
                + " All points passed to the Bezier polynomial must have the same dimension.";
                throw std::logic_error(err);
            }
        }
        control_points_ = std::move(control_points);
        auto & storage = get_bezier_storage<RandomAccessContainer>();
        if (storage.size() < control_points_.size() -1) {
            storage.resize(control_points_.size() -1);
        }
    }

    inline Point operator()(Real t) const
    {
        if (t < 0 || t > 1) {
            std::cerr << __FILE__ << ":" << __LINE__ << ":" << __func__ << "\n";
            std::cerr << "Querying the Bezier curve interpolator at t = " << t << " is not allowed; t in [0,1] is required.\n";
            Point p;
            for (Z i = 0; i < p.size(); ++i) {
                p[i] = std::numeric_limits<Real>::quiet_NaN();
            }
            return p;
        }

        auto & scratch_space = get_bezier_storage<RandomAccessContainer>();
        for (Z i = 0; i < control_points_.size() - 1; ++i) {
            for (Z j = 0; j < control_points_[0].size(); ++j) {
                scratch_space[i][j] = (1-t)*control_points_[i][j] + t*control_points_[i+1][j];
            }
        }

        decasteljau_recursion(scratch_space, scratch_space.size(), t);
        return scratch_space[0];
    }

    Point prime(Real t) {
        auto & scratch_space = get_bezier_storage<RandomAccessContainer>();
        for (Z i = 0; i < control_points_.size() - 1; ++i) {
            for (Z j = 0; j < control_points_[0].size(); ++j) {
                scratch_space[i][j] = control_points_[i+1][j] - control_points_[i][j];
            }
        }
        decasteljau_recursion(scratch_space, control_points_.size() - 1, t);
        for (Z j = 0; j < control_points_[0].size(); ++j) {
            scratch_space[0][j] *= (control_points_.size()-1);
        }
        return scratch_space[0];
    }


    void edit_control_point(Point const & p, Z index)
    {
        if (index >= control_points_.size()) {
            std::cerr << __FILE__ << ":" << __LINE__ << ":" << __func__ << "\n";
            std::cerr << "Attempting to edit a control point outside the bounds of the container; requested edit of index " << index << ", but there are only " << control_points_.size() << " control points.\n";
            return;
        }
        control_points_[index] = p;
    }

    RandomAccessContainer const & control_points() const {
        return control_points_;
    }

    // See "Bezier and B-spline techniques", section 2.7:
    // I cannot figure out why this doesn't work.
    /*RandomAccessContainer indefinite_integral() const {
        using std::fma;
        // control_points_.size() == n + 1
        RandomAccessContainer c(control_points_.size() + 1);
        // This is the constant of integration, chosen arbitarily to be zero:
        for (Z j = 0; j < control_points_[0].size(); ++j) {
            c[0][j] = Real(0);
        }

        // Make the reciprocal approximation to unroll the iteration into a pile of fma's:
        Real rnp1 = Real(1)/control_points_.size();
        for (Z i = 1; i < c.size(); ++i) {
            for (Z j = 0; j < control_points_[0].size(); ++j) {
                //c[i][j] = c[i-1][j] + control_points_[i-1][j]*rnp1;
                c[i][j] = fma(rnp1, control_points_[i-1][j], c[i-1][j]);
            }
        }
        return c;
    }*/

    friend std::ostream& operator<<(std::ostream& out, bezier_polynomial_imp<RandomAccessContainer> const & bp) {
        out << "{";
        for (Z i = 0; i < bp.control_points_.size() - 1; ++i) {
            out << "(";
            for (Z j = 0; j < bp.control_points_[0].size() - 1; ++j) {
                out << bp.control_points_[i][j] << ", ";
            }
            out << bp.control_points_[i][bp.control_points_[0].size() - 1] << "), ";
        }
        out << "(";
        for (Z j = 0; j < bp.control_points_[0].size() - 1; ++j) {
            out << bp.control_points_.back()[j] << ", ";
        }
        out << bp.control_points_.back()[bp.control_points_[0].size() - 1] << ")}";
        return out;
    }

private:

    void decasteljau_recursion(RandomAccessContainer & points, Z n, Real t) const {
        if (n <= 1) {
            return;
        }
        for (Z i = 0; i < n - 1; ++i) {
            for (Z j = 0; j < points[0].size(); ++j) {
                points[i][j] = (1-t)*points[i][j] + t*points[i+1][j];
            }
        }
        decasteljau_recursion(points, n - 1, t);
    }

    RandomAccessContainer control_points_;
};


}
#endif

/* bezier_polynomial_detail.hpp
1X7JR/4ZZ7ws6GXbrfJlwvvo4Nmwyj7EJx1OKhjvDaoshqmlGZqkdjDz9gTrRhk+wU/WSS6KxMU5fpBkS+ZUY6zDOA+KzwqOetN3o8mdaUh2wz3xKpkXIRNg+U/keABk2++AVBa8BaX1jzUdq53Jhbq5LA+kpH3riWrwk85tAbMl8XNMACGkxQOl5PVgKDktwUvHWbt85QdAfQH1056MDbAxIAZnNmQq8izyOoVcQM6oHYjeCoYBhrbzRUT/tHnv0zMlNFsMGDdl40SWq+k32GqzArkVzoa5P7D7wjskJzBwpiwtSJl0En7/uq6hOVAlORVDDlyUHJjRGbz3QwsPHOruQgJ7HslZtOfOxMS8Q6XGyFWlsiv2P5CTlAXHXKBJNG9t2yMBeVzWvW4sibd+Vd4LHNn0I+NOz8gtURDrqMggTF9WJpWmxnIAEizt037ww9TifXjZOHLyb4IUvSb0B1SDTFGLcl8N72dG0go91Gui2ItNSgef9O+C332TZ99VWPfEHlGhrbPxxOwLJL5w8tvtseTYvE4EaKsRmJ17nCeTGliD56PBGmf6j1IaTbBflZ4UnY/cKYHsR7FXZy7g2OH6b4CQHRlpRfs26uuZKhK/08MK1J98nYZ8zmJDOBI5UmNRJWkVN0nn2rduMAnxXlZf2zh5C8nijqzZjZHeG7fEZoiyEo05SuQv6fMvTqSoZXe45q4FuNm28Nb8GlvwBtWDrDbyoDLcYG3l0UdAUujXvKLxB8fg42aT1XTLvuvnrt8gkpluHJGyIMWf7qme1RGPlAOuJObYZ98QeUHeyG1W7gcjZfNuqEh/1QSR6VF9Hnup9bg2d7aRdiCu3aHrmM/r09uAAh9k/NihlxHUEUwVbCN0CmWF7i83QSHd81ebY0dY818D7aFJ3pP0uBTdazx3LHY1/idnRh8BkZVoUP3kUQ0OCyGu4LZ9abFopvlFwwXLK6W0HBGbIMf3nfnuYDTNb/LuwdVaD2rltCyiNT6j9s2ZH+BN3+8Iqk4+i7brt5+iqo3ZjtJvkRDDJJUfRO/DBwDESRxBh6Aqk8iH7xWRi49cQKF3OigJ8MNBMSAArK9EYLp4etdbfacTNiOa4sH/rMZ+mgYxIqMqIJ7P1n7jLLq9UijE/H4Q4j2tUWPxjvTsPPPHP+MD8YKuzwiRtW1qFPkoSuN8PEpnxSl2SIH1cwPj4Sr50TdOX9mSudSJOaTM32z+UT6YCLhTIv/WRHAineCnT69TgB7EwnEmop+NOOTGvxvnA6E7a1L9HFTk9sQvBHtm/4fz2SzBLYmrpMCxdhA2isxNUiCDtEd6c5lsiNJv7RracteyQElNcdR4seUFu1XO42wwIMEWFBfDNXdRPW3Yicx1z2amoU3iCsby6ceyv2HM+oK+4VOnT0lq4gCgam//EKQB6WwRPL3JbO59GTPvEjGBtT2HB3W66cayY/PBSaURzbnIfrj/mugbkysDeYrk99/mN/N61CtmXPhxk68JleQLp763rg24XfxHbtl+tfXZMT11BHN3JZX1D+ECxRDuTHi8xNvCzTFWIkC0OsnWe/dOVzWTSHOOaMvUEJfublLqSTyZ0qdsXhPYs9rRA5yWJM9OR9MK+nVc3SOUji3vxVnM+QCkLR/pOSeicy4VhgpFXrTcl3E6Qw4mrTfbbQntFW3voJNKD58N+WHvEB+0TdHY/dvobfhzotRtrd0Rr/cKC/uR0VYY2IGZgAIRncnAXtrFa7YacVe5ak45ITWyjGZhQCIvHU7VZJUS/1dw2bKylJY2XalqnbTvYhn/dlv9pKiy1fbVnPzz+wHuAqv7Mwtf+RUiACl33dpZPa115wzuPmPJJh8YdwCa+Nj2kOZ+zKjfyum4d+QTSfnNj2+LFCCZXOYHRkKCNm0lbgj5evXYLXRDB82FLV2vMlvYF/x5/QMv2b9ZQhW11mSxpYbq3tiVquMWGmhN5QtBPHtHtOK07jc0ODDj16qGgI4H2awegKgIq0maQoOI/xS2Zv5FXBN48Tv9kNPd8DgL8x8d5ftNPPekIEd2yukBscHJq9QONLlak7q8tHD3esZanNkq3mapV6rafZNU0osg4qzVK/hE7nvL/do2tqKoDhm7FmWaHTGgXcM/NFTzZC2eDFYx8G2DCCtnRq19gENCmHTBMqKthp/4wmdLQuy+mkc4Ad9mLK3FMWm///oLY0H4ei/OxEfF4649o0pWXvuADBx0AaLK2vL5thKiUFKwLcuAWZW/DnHQE5yIU/6XJ5kXZ7VGAjxMEYwEY75xmQT3zDa62q+6zVrE6wL6FpYdWbmjn7aXzavwiqwOCvw7WmfrAWugWyhqW8598/n9UlO+AJjX+w5H9XOsnSc4BV6LFJEo2/GZmnnBbr/vSN/HktePIMzJsUE1y4O7uFE/71wucIluP7vCgcFEeRt0vjALxcoKl6ZfSnONiYWKiIZ+/K8Uu6a8Fpe8RYOWupSyCWGZZahAoFaZ8yRz/8DKTP8/8mt+NqPfm+s1YAZ93w8dRZe7eTxcpMb0Pt3T/MPH70EoWI4EcV/2Mxh45nbmx3OxcdSehJBmHsEJioWsU/McMaRtVIzNn6ABgQJ1W/OIqTsBF/GVCRL29CIrFsCNAvJOqKJd29J6WjELC+GIHf+Ik3Jld4vzFUcjBhRMZhCuSceBygZm/l+xyH8+v3yE7P8GC3y6eqRx1fuzdc6Mh59QX3hEu4SVQuHfQ9gB6jRXuBcreMhU3dTSAx/c4VxvQbYs+h8iAkLfraY9VWvLKXo7AyMzTlzLkxa6iI8xzOoy5qAebBO/S5+HIhuS5/lmEdPN6liQkBm8S1+28o+gFzdhFF5Gsmq/VZzAlyPH9rBdrEai6KHETZOGDa3WUsFcdr+TO8I5rP6yTzh/o5bpFZI0o+yHv7aV27FOoeujslQOt3frF8K43PsS5CexgeGmDMF2j2Iwy/7H5umHHl0J4adch8ZZqohhltuvqxC3KHz0eZTZgsMBSWTBDHkx7hidPL21sqBZGSOPHqPUGJ3wwCfks6aHyeazVr1lwHcXIuFphheX64eWrEqoSitAbdUnPdLuSl49QooahPTnpedex7E2l3/jsaRRbtoqPqDpcDpv4zU/c4ZYjLAN8ws9Q4a9ElWyk5a/3j7QZ0G5RiteBdCn2ykroWM+jx2eghX6YOSzcb0b7L+T4u/z8MNmr7QkAIb/eDC788uE1/uegP4tTLaALSi/MDRbeotojU22cH/qknMONAGYnAiem5IohPxMVdOfhEji3qjfLcJlP3cnUdRNsBWsyuBRE92r/5qCsU4eRJs3/oMmQDcMt1xMZxINZVhyUP1h4k4DNIwEYekmqqdteJdQ2iC40vS8WOs+2mp/U7Nq3UOg7ldydSSqoeCf8mUzL3YL9LG/cYjOx7b5zNpwU0NfY5H/rA7ufkDx8V66N7Z0XiOUvOx+725isOh3mutISAalcq3E1MKlkx+4L79YGX4p7aTMOljkEmIR3chaiS7J8tAO+EyKw766SVtkeixPl8MYOCNsoojzPH+IiKadyDB4nG5dIwrxUiljg1ZQnAOUGGgnP/GmR+W99fsGnPRh5HWTeNhclOarVQI9dkHLBOpee+T0RURa+dSiZta+lgkwAvR9MQOnQ1IUaV0bTv+3EPu81CPI1wI4aJ78sszDodpMIDk9WArpU+lrePZJiVLuK72aVFqMxLERhbeCX7oZmEoBFxTsAeYH4CcoCQjg9+tbt1iivdPN1rAyKqB1nDDeNubqFNb9Zq7qC4URn4Krn96MTVH4IjFXUleNfBA5FG+p0K5OckwmM9iyTWqEpd6VVTjUAov5+QqleyyQCfPKWusDB2dy85Ihofba69JuLVnxBHur4uZ2kacpbCt/C5ozn5Kgm1Yi/wsxwXOZ9Ti0fMqZQ1HIFHtV8O05gdld78JmWhUMRQDjX/wNxc4kgsL5eEKngF8Q0oxe2sbauN8K/UDro+ro6eNcl6H6wg4NnF1vcOF/iw2mC8o65F2x8pbl2hTnrV2M7PTB2yRSSMHk51Ifj9n8wYApYiOyscIJqwKDFaFQnMv9fpKEHG1Je/upeV96/BQz73GbyMlD08xjONRGRT3IPwvPXSkU44ShefvO9yaKJJvUYHgpWg+M9i6V9sKNBXlQxhvhK9nWz2sgNOrwNXBQzPn6fG3Ji60P1VBjJcifSYvdsLT+kvRW4IOJzFcN6Ol9nW3MWFHBI9iE3wP+b2dphnfwtCm1IOJsu6dKMl3iCl1HMl1Wx5KhIoIXobxA/Jo/2bpr2ux1vdVsclFO2aib3bN0lEflduUdE4EIco3g+SpA3YL8AgQZOQySwwtcQYYVv0hIDeDZfIqUdC5kRdo8in6UmpvyqhZrQTQo6xKk6nSWBX50tzue3gt6zKCNGyT3A9EMO8wMO3hGJ4sefsZti3M64lZXZgWpgOnh1cb3FhvgdTUw4vDrAHPrl0Um6FC2c1fsm1UEEly6i73tatbNaHp9bD/KTf0gR52ccbcK71EFYk1BtnUbed8BDnddFGbUWOuRj0tIN2y3oVtu5CLRjIUro3Ru97rooIK++nrUwvJwGUHOdyuhMJD61OxfKSY8sbDyQkhub1ZraXelVhK57HW6KbJ+8xIOxzfmYjRWNwxsajLOIEkH3jEcEXHe6kDhUDRTdT6WJ0sUVrjufIjcFtd21kcdnOHtBv01P63a/rYuHDkg39RjWitF1FvuqTuGG3Bb8S+zvopU9z0s13+xsJE8Hjs0vyqnzulzA1lqqiay/LtRmCZBoT0bMg701U+jVpVmtcJws/+VJSUdka3KIreSZ74FQ33hu+g/D/fmzL9+56Wt8lbH9Z59hPyMbt7C83iDzEDPL3h9/1N7jSDN5NBC3THUABFNt4oZcfgxhG0p5Vf0W5daEYTP6V+eEdc+uHHRmHp33LHBnYGM4ZcGq3cM1ebr9UUyz1F4QGWks92ooeZGRLqHW5rMxIOVwaHXxOV1qlN/8HLOKQiZWkiJhWSyagQ1puJ7KVHYqplSMFh9u83RXs2xS7OkYC8HCIQ6iy9Rmh5a/YcsHDPC85UC7B17jq+nCsNY0JZGQYXCExJee4ygGjGNPOVQiiotQyiNNn2Ooun08SDFlqQN5ctd8C+2EuS5wke9RdbPGOAsfozDlCKYTIiKryuWlXBAVdtMUHglQqznu1E1i03HAvL8pzcL/QWvOZblsxyS+3xzEeyO2wOPzp2r+B+LL9hUhc6gbdxIQFyRPJlytuRT5L1ECGsEbEFtPlh/0bjMROWZs+48NL75C1Sxk7QD6qixbk7v3d2rNvakO4t5sN8KK9Po3XlJwqh+uzWRT145tkPpuOhoVcAdRIdUeaxSHrStzu4PjkyD9hz+W9qs51XHEA9Gg5Zf6MfjkCjsQk+B4Uh/nFoM7dHcyWTHTNJbGtaP4hDTzbt17d3vMj3R1JBaC9vetlhjVIsOVBRTp8VFZ0zGQsVWpRPwof9LtPW5RTNXlUWR2FBWtOPmTME/Hd2BTETNFd/WfkJv/apk1r73ac0Hkn6p39L1AEflI/g7z7DN8XFSeAQ6sjv0yzA0kHUcopyEBoOavpc6yhbqcDH00T5xR4qFs8YzBOTTZBvB2m2pRwrPHE3oTzzBkM0HWCAyP6/fJ+qr6amF/B3Kryinf3CW4yGAejg3eI+cNEDyuBaUsc+ekbDIkK/YFrSogD3C4RQmdjcboDr4NmxYrEHRx0mLG/ed4x0hcTBWnqEHv55Yxhvjiv7Vm56vQ4Hf8GI9CWMtH614ameKUrEW+Sg/N2p7FoX3ntw0vzGJlmOStNT4xlxG1A7yyOJJGAbpFrxLg1pkHqjP0eQCNMe+hxspcKbgq4Mn+hCs+FlvdlhVSi+So/f4GA3FLGP+GEcTLiolv/s9LZk/ngt4L3tt3qFgm123NBozLsxBj5A619/PpTT9nKP4RNiPlnuxKb06XqKY0/LfD2OsuHBkccldsRcv2XjLhFlhUKzN+rtWVlFgTgYSRteX2jWQHZCIx66qmaaB+gxa/IVgm+0DwrFUfufq3ckK8TmFE444iQGoPv5eNZ25G4NDwlbboyDLN2WL+cxdAfIArAD1TOig0sMy+3e7pWKRkbyE650Z/DH+jefF0NuD4CmgIYdTAtl37BOaN92BZf6jahq5d9VHZDFxHhpEpdJXh+5d+qedPKS0Kz5IxTRmAAJemTaMVnyiPKTloGXGmwzDPD2TwoMWqB6gQMUVKpCf052Syi0A6fV8NRtrlTV2R5Kbc9DrblXwqBYlCFtSorYCaEG7Nd6gHqEWy11OpjrQmRNcX8zHkezNVOESecLBiovEmg4Br/7SBkBPjN04ds8lyyUOmbOtaXFr2q3cEZ07pFRdWcW9QoEqYEnCXhBQmNS02c7PFQP3h8yhU3ngfUEYRx71ipYauAaKTPhkQK7kcCYNnsyJ/i3/+XqVi7RCRhb8wPLsSA+mdXnli0zTuSEdZrYBkKjb298V3SqPbbtCc2wgQXgY3DywO0kseX1nNm7AkbO5jKnadJiRPTDf9CT1aEFcOVZ2mvEVP+CWiHjY7KteuYrwKy7JwPT0tMy3/e2TaFCuSOz1YzS/W3lwJWSfVwHVmardgusludJF+TCgoOZNo7xAF3pTIKfNu2WpkMNPVzeG/2Ytsre+WFpeojvVgm+whEgYzedMyGfZtb0bgip3HYvLLqT4tHAdtsSGUWxFXWMEsTDYgUylKIVbw0zP3fvPWHlmtWp9fuhiLxct2qHio4nc3bMO+8Sh5fgkQXPgANOY2eEYU/x8vF/aLbncIH3itCo7CzvLyMKxCWEokRkDiug6t/qjIXq0hYhKqbefPNVVTC1giv8xA4FRHYeBssQewpQMwLASAgPtdNpAAqCj0F+Njg8Dq0AK2GL3rTG1xAG0wkoOUuSi7SC971zv0WdKe8fg1Ta58o0A61lWqzNNOZQIOdaruGN0boyWYqiXudmcXhEkbeIx2WRJarvqoX75yhVAnkydKVvOtnYrZSnyc3vZNq4PNxnA3Ek+RADHq4MfDr65qPbMesMVe9CzxMJ5+PtWNAzwls5I6ynw4oXbA2HsC+3R0jlZRueXdtPCNz58mtyWCH/A6T+w+ZTUmQkV7fKcmVyDnXaHzLXGKqzMNP2KWJ9kLhFq5c1Zzi7F8kfHCzdhYC32bu7mlCjiumFcTUrio0NVj6p2hoCf5dCZHrdW/v41L+11DdaIrQJtDigCAeYZpoWMmn+qBDE1zENzNaskWUNJ/Fn/Rg1Fk9QdnI/em8fdiTscmZHKp3uEqfhQSqucy4x2hHV2dygYs1Vy+5NjSZCC66r8fWtgx6dj7aHOM6x9OCTAVPwmgdeVr6GH+BTSTX7+k3Rrxtauyu6NqAnP5sAjg9lI76ATf1H4l2TABErAE3YDC1Mjv5pHX019s1TTulXdKtLj5EIngEPRdTC/fVOZaxBTA9W6NLErI3ehKk4/a7qgiTomC4rd/9NRU6cQxLCEoQVIup6Srk/GKsnbWMzBJp2O3mSBH/M50VHLE/wrmDZ6Wre9N82XZXCF9GKJs/dgKjDV2qVoTc16M7gG3/vc28kjDP32SyK5ujtt07WFXSJ7uAc/0q5AnKmNqhc0mkij
*/