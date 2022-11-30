/*!
@file
Defines `boost::hana::while_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_WHILE_HPP
#define BOOST_HANA_WHILE_HPP

#include <boost/hana/fwd/while.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>

#include <type_traits>


namespace boost { namespace hana {
    //! @cond
    template <typename Pred, typename State, typename F>
    constexpr decltype(auto) while_t::operator()(Pred&& pred, State&& state, F&& f) const {
        using Cond = decltype(pred(state));
        using Bool = typename hana::tag_of<Cond>::type;
        using While = BOOST_HANA_DISPATCH_IF(while_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::while_(pred, state, f) requires 'pred(state)' to be a Logical");
    #endif

        return While::apply(static_cast<Pred&&>(pred),
                            static_cast<State&&>(state),
                            static_cast<F&&>(f));
    }
    //! @endcond

    template <typename L, bool condition>
    struct while_impl<L, hana::when<condition>> : hana::default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename L>
    struct while_impl<L, hana::when<std::is_arithmetic<L>::value>> {
        template <typename Pred, typename State, typename F>
        static auto apply(Pred&& pred, State&& state, F&& f)
            -> decltype(
                true ? f(static_cast<State&&>(state))
                     : static_cast<State&&>(state)
            )
        {
            if (pred(state)) {
                decltype(auto) r = f(static_cast<State&&>(state));
                return hana::while_(static_cast<Pred&&>(pred),
                                    static_cast<decltype(r)&&>(r),
                                    static_cast<F&&>(f));
            }
            else {
                return static_cast<State&&>(state);
            }
        }
    };

    template <typename C>
    struct while_impl<C, hana::when<
        hana::Constant<C>::value &&
        hana::Logical<typename C::value_type>::value
    >> {
        template <typename Pred, typename State, typename F>
        static constexpr State
        while_helper(hana::false_, Pred&&, State&& state, F&&) {
            return static_cast<State&&>(state);
        }

        template <typename Pred, typename State, typename F>
        static constexpr decltype(auto)
        while_helper(hana::true_, Pred&& pred, State&& state, F&& f) {
            decltype(auto) r = f(static_cast<State&&>(state));
            return hana::while_(static_cast<Pred&&>(pred),
                                static_cast<decltype(r)&&>(r),
                                static_cast<F&&>(f));
        }

        template <typename Pred, typename State, typename F>
        static constexpr decltype(auto)
        apply(Pred&& pred, State&& state, F&& f) {
            // Since `pred(state)` returns a `Constant`, we do not actually
            // need to call it; we only need its decltype. However, we still
            // call it to run potential side effects. I'm not sure whether
            // that is desirable, since we pretty much take for granted that
            // functions are pure, but we'll do it like this for now. Also, I
            // think there is something rather deep hidden behind this, and
            // understanding what must be done here should give us a better
            // understanding of something non-trivial.
            auto cond_ = pred(state);
            constexpr auto cond = hana::value(cond_);
            constexpr bool truth_value = hana::if_(cond, true, false);
            return while_helper(hana::bool_c<truth_value>,
                                static_cast<Pred&&>(pred),
                                static_cast<State&&>(state),
                                static_cast<F&&>(f));
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_WHILE_HPP

/* while.hpp
R80iAecR7Ns3nUn/ijBLEMk/ggqpjyMp9LUiosRT9fhl/wyvC7HMJ7FpZbcln4jyiHbBf67MMwXLr9D72I8bo/NUo4cgCfxqYKqI4G8MH/qGs20MC7Ijcnu8NQo+INw38wRmqZKQm2NEwvRPgk/C2GcnFyjQOon/ynQ1Ib0RX9AxPvBNiakfG9fNgOgeI5i5XgiPJXwNEb8SrkTr6nLEoS1m9E1vUM98Bj773ggdrUG/zpeeyXYRaJ20hMgLZ+oOfMr71vR6MpvVbAIhi5Kj0vBF1kOOrAv8l2MfV2rlblYW3gWt/nC1Fe2wi8BqntZmKZpm5ibKyuooCh7XtWEX/TEWwHYEEONo09AcYLGP7I3mwqjnS1zE1Cac6WHrV4p2O7pIS+D2LdyxnxHJNr1hXhZYoJYbd4k5Polp21DuPbI5ADwUHzukE/WKSNlAuB+R/QZgnJTaiVSdLlMdDl84ShCAo7Gz94aKQ72z1FJgsQkB0Z72X5NBricjAYKO/rXS3Ybyb3+/SA4Zr94bDdk7w+qkHjt3RQz+4NkBnGu+0CR0ROgvGZfgHKV9vn53m8DUHoi3BT134WWy4vK1yI8v0lThLipC4QBYLpT1gH4vDqI8+kGtFnSKS/cxwLdEyMpE8yr5Iaj1djNhWP4HRTN58soQK3z6lvireU7VaoiXriHuuQk3G8iBNGh4qFuzrqtM1skiXt+zI24Ribsz68rqQ4lvB8ubRHBnfSbOnjY8l7HvOjOG4QHfRfKQrwrjk0/HBJUPW3mpPngAQICwNCBAwK8/pUs3HP8yGDuTayAzX3ZCKFOTJ9zzggG4250AxAQfBAQiRX2c6I+ujhL5hp919vxSpfgBRsmuFw+ADirYvHdVqtsiyZCNZPbgyYsCsCgB9BLVznZuURV3cKD+i4z3v+o6BaEQ/M18y3VzgHjOLRQDE/DiMlFKK9XIjeRCN0i6z/nWitaY2KcMz+qMHTTSBtnxzRoP6+TC/zRMtKtsaAWU+DPrr4sKMxUmaAy2u/GibGJTrqlVItmoRVWl5t2kvFyC9YxBGZwm3ZiZei/CaTHO46Y1uGnZjPFhJfrbJjI7BbwKy5jG4YSQ5Y1lF5jZs1gkRTbX/iWMmKrWyG8BlrhEbTNBk2xQa3WmJ/js35K9tpM5RRGw9vNaqwFUYJGPwcImgIS3fYIReS2P2PVbd5Wy90PbD29FdYLSe+bd8PfI8yLtcT8jIrA4nVpiJYvFPkAqbEWXE4E9BRk1yjwkc6P5IvcqvJ1iLgwrY9uiZaBA+Wa2E0rTdEv925YuR8VeiLJrN1q0SNK5b0TLPI70WYRa5+kYhUw5RLvVzFAQ0WHXi9PuOo6hI7a7h791szygh3+VtxjMuYBhcAg7gIMDqFi4xiS/rplPdVlcmZBmuGXQcY6Ap/QkSnVPh8tg2ogwNBIaFNaWjWISEIda9yqCpCTZYMLrX+za1NxeDOCmvLVbzirwgC/bcRnuhBdcDsjJKfHIUrmFGPbWeI5dcswqL7mcqt56fwnPLcbbe3ghpH0iyOBFzsoiqCymiRE7uKMnfQkbUcbKF8NBnNfGcMFBamgVtF9otluhXPJuJVYrpWv1gHfXF8FkHIv7KZ0Mj+RdzQx3sYXZ3gtDEn79QP2Y+25iZXRJu/1XUOlfNjpnSOy0OLcO/sLnQmw5UddCrFErvvRtzBi12pS5gXJLSLFZBqwOt8Q9Z3EjEFYOTOvzCamMeeGOvZmmFQQ83byAJtopju8q1snEIMjjTxFm8XLJQZep6SQk8XHTtlmu7rh1bcSM+sGfnj/wVulC1fRNKxjKCCsSugEOS/X2zgLuEl7rXxD7zLntigHVwFIIVSy9sjje33eBnZ5zCsGNuFYVcOHlR3k51EE8u/sjUGi76fzUMn1lt1nhZbXJGdGCWbTzbmq0FMyP/8zcMYnjHKNX0t05FUHx6CulrN68Enztiv1re9Rr+7XKi+cvHiO/NUYohaw4YH4LCPBxH2E3w+ivQg9RYLhYfBC9gzTFlGM58pS6F0DZv7eD9C+9bfU1g5w0vCX64HyZJI30PtDrFnANaRClnp63tA5zkdAIlqvqBxD8MRS4y8f+rN1HWdZ6u/9qZPzqP4ou7aDHUqZGSWYMeWTmgsGPzJlLTa0OvPbMk1UI2sQC0QXAA3uooT5FnaidmTqMxNkKyGDDeMId/t6oW46PcfW3dIMzJ8KX6xkDMrUmnmkkSdia0lWjCWkcC4zYWgjujLwRv9PE+1Iw3EZ51yh3/GSPYClN5Kpw0elbCwY2+pPnq8Fl3XVDed7bWuSUBrj/skghMcO6t1gyP59rwqx5vSMEjwb/FZnvNvmKpHnZg9cRiPKzNfHT5BZ+hI/NaeK7VVcZfkvpIzGsTYSEYGi09gv6euHaQ1CSmM5WMRNktHmfn+mhdqB/VJZ7n1v5ecXdxIi8HsA/Xe2YF+hf7LQldabZ3ezgm48TeHW7Wr4CV9l//J4t4LhYsnc8nZEpp52UvTt7uVgydSS7KaWBfRml+Tk7pZ2kdzZ5kXUsTWZfNSf9agrmyPz6Xx2NJ/m9VDNg6JZxifxDXuRfbvB2H1NyVf0UaE1v6+oV/cKD1Co6JqZBxB+1/42JNu/44eHinlbFHq48PacSZAsuxD1y0UACo48ibw/Oa57Dd2BnPNDjYk80gCnRKDuKRWDPCTs8gah39fwVOdsJ0IKTnSknhNYHM5wmVOs/crm/7mVluxN0uO4403WTDpmhcTUCn9k8mM+fD0PNAVNTH6MaCZqDFZ1G363chVeoxxlsI6z8L9NTqomtu8xzllD2snzZ0Jo0WhMrBRC6DIAVACG8VAk7eZ48j3UkqBsEI0f6W3EkUTu+4HuSHGUdGN0faiMaXszMHyJrR80Co4qFWm9AGInXRgD6FYWdXxCmaJXKIPKfuqNdHJUc5tukKsm5av5RRLPY+AjfBi8uFuZ/HnFvJdJJ2OZB9/pO0OFXIe4JnGHy2W5Rgt/03CYn00yNm0qu6ZoWcinLcp9H8FA16o2xgmje27fB6Lb/VJtQBXGcGzlaZF0MKaJw7sJftoD6iuFw8/OxKifcYPYoE7YL79H6BljGPNRm9nK4HDOWRx9Y5W3XAxGAUvjUJ/hmQl//etUPEatYlgUeeFqpDnWtjhXt/o73VO2vEz0Myxl4N2zLHq2PXqYFnGJsSzD7fFx6Dmcje7fMtNDinJP1bvLEkszgAfIMqx7m6k0V5yv76ZJM7V75CzO9A/WS7nX+Qm97O75fvyxSlsaKd26tpZjJvsav+q7lwl8Ul4jv2lcL6tTJymEXz/I2vR8sAP7OZQZYfUAcdUujNq1sdlC7Vimh/6K6ge42A7xISyy+ObWor8BEn52yRNsXmrRSmzi8wUyIYyfT/6WOhdoYy04yW5hLaMayY3XCU7QYrWzrRgQUPzIP3aNr1v/nPH4XwBOsBhltk7KdFZ/voT8yXBJnGpByG9Cg3j1XfC5encX4w75TJG1npEOa8ww3cmMcnlkY+3GEqJKc/tsGKx6aLnKIW5O8loIUpnRAs4TMVCP7F9rE9Nt0ucB2f0OmkRRyt8wZD5Sp5IWga3nao3+NsKiHo5ZwCz9ybzoT8OpSbaKSXaNjl3LlLZzbvLH0MbOLLDlTFRKd4Clo1Xz/cqUrZlixakQTZYKbZo6+kAbaw/alnr+DM5TrEZkHAhYZgf7smWO6NLUABSz60wq/UpFFLX/A5icFV2XLyASIUPXVVr5Y9jowij03jacKSdTxJvRTX150ZJ30ljv+fHlVjlW4aLy1sGS9DFen+57cWo5INmBEv3wpYg+j3X05/wRd2WutOX0saZ7mihYN6FVQl7o2IIfh8qaRrFoE6Vzg1qbZtGuZnoq1KIBpJnwNZm8IqlVPGGFhrj7Bufjj+ekFqiulgBeP635EaIFJnodPs+xrEs6QJtoaIzR/vP26fkDi/vVuvKwKbyC8ZQorNOcERF/fjNeMyM+uLPu5rEcu3dQdTeBBJY2sqgbpsc4AmEqulkFIA9KRfE/Iyfhl9ApOVEspzRlyw3T0K+Jm3vC/m5VvLgN0ZN4ElPuozd/1YlxtqKYdHHVSO1jEyNIR5Rjp9YZAQF/PbUkbY6TnG36fLhdl2XkqjxTNgd3DucY316gm50D58fy36DWQGl51mJIFb9o79W3Q//TZJrxazDVDbZIHl+p5N5V/pZXEkK7QSiLV4Ug28Nu55qx1XWYSXVMcLktlWZv11Mh9DXF0litgdZUarRwCsAsjGrHVfFJLNn1NGrE93yHWKFGktlOovZkFMoko55vfVpnGBy3RcBOnBLj8eIwaz0Z7RiOKwuOKvLYs2VQnuCzoWoqUxQON72RzPrXISSJT7lv99v2GAon4icYbLaoPdPffkzvwxk6FqfQhpyIWmHxhoddrYTW/4azhxIwAbOobhAWqxrlV8m82DKrKB61yx57wJqasJxYOiiyjaLlFiGgla6UyEJx3rxZ4nvdL48NQRbpEZDyTu44j3TVfduv3Bn2TG2Qd01423E78DzncVsmeo5s3wzqW6y/vW21s1abv5WPxkwltUG+thjul7mtme8A1dV45rwQK9df7X2Mvl7uaD4DPdiZXFhPsi6zfESAYTa1Vb73iphAa+5NLbYpEu8NW5XakXAuXbyraxv7Dx3Y0S2tyVdW4n+hU1IV5aZjH4zMtYt0iT+ZhvuECjwZbwZ4vyStktTvCPgPuuzfKeyHYXPVAP7Rqkn1WW3ND6AxSekbI9+0OeweQTux2J1YEnwIpE+k7OG71Fl1IwdKPaqMycxQM49lJfTC82DnDVu16bGfuJsm4mE8+ZbTd5NkxPUZ3J+dkb4SHkIBU5fqlm6x6XtrO+beSk82o1RJpBai1tihh99giYq8n+rBxL6ZM9HJ3ok9tEtIMaeXbZIW/6gzneoChPIrFKXts2vQPL/akXgJ6rWNCeKQq0xv70e4hgvoHKMHWsQTHuFBeUbrFvfnyh1Xg4aXGzi/du1vGjXBz80DLL40MfMl1F58xc+c5SXeyJiAmnq8Q/dBoAmP6zIPalSrt2CQ899L41Vlmcp3alkUegN7OMndIlcWzq5ocEU2KjtnQslbjppy2V+Gb4aNExoWNdOIqOCJjPX/F6wVB1z07G94FNq/8pHnjg5gw3OurCMg58g21wr2dhmxzs+OM6Knma7XBnN3N5ZVmztFplmrWNDKXhUzdJW7cYTEd5sZURg4rJg2d+EjPukTHmsWaGNWpYD59aztvJJhc0rRYVB+3HjOrxJIa4YMLryTyVHRSTXuAcEp9uVNrWhuxR8FtcqVCy1Qwt+OBpBlxBbvU0y1AZ2LZrb0vDj86LnHQxlql2imWSs3jgGTBsTHWn0g6cqdro9BztXKn2Wrno8y9eLsxerxpa4XwemJpLPLK++Vew8ybfd6QoSFibRZOQ5lyZzsyTW4UXOO7c5OcFLyuLVlj5yakK76ZmXsW8yYp5zQ2nuKyHJabqRvcJpl93QPfbfCyjM1HqqR1XoxUaHE38C1vrXK3Y4aE6tyh8OpAw08wP97jrc1te44kBe3DG21KUUIEFpDRIKBE9s5hQ/SXpQbySlW4tki21DSB0O3nhi5r32p0U9PXaZgEafXkS2DIM/WUDTISPm1cwyXbvTEhTVb8GM8jIfZMHHaiGGhYNru/4V9q7wlA7waDY3dOAzhgHr0cjOxaG5D5xiLCzWAq8IHOUc1GDveaS4PHLIpXmbEFvVU/0eL8YT6l4PIRJQfgRuWNb4gV/4f5OeRGBRrn5W3gXhydmiYPbFTc8vqgbwWNJmxUY2w94FHBQIEd/mf5xzdRRIdoo3NAA2qGiEsCSDl3xxF1VBzGK/lg7LwyNRD9PKPDOJw0GK5qz9i5uwp2QyTo76YdyI7SsaA66E3fMnXFme0YUlPTAplrqe5nfC6zzGzR9G3c2exB6+rlmY78bHIdcn9gspwOb5R9O/2J/tf3C1K6TGiY8k27mCRHyYF4uD/c+R61Yem+pjZTzj3EkjeDUf/+0jhpHfBDIFL9572Sdn2qe3048wdOXnpmXL1VED/UqOL5yYMow3dOgd19WClS/DGNh0dsko+DJt3u7aLaTqruCYQ/ueBN6SqcEzjQHSg06Tx/Wy6+InTrWEh37BNxwn2Tz8tQP5TY7KKPT0FXYcloSqjkBRxnSEcA2SmqRSopEyTieVGe5m4246AR5ffeY7aSacfrpUWnccJdcBxiWOt/OIRhbCQQtbIULWCfpkOMv8wUQmLKFHo+omBp7lYOPcsnaO/Kn4t47l6y6tNVrm8CzTvATwH1MtFRPB+OijgZ2XUDZ5jiAheCc+7xwq8H9y1rXXZaeC1dKhtvhr3nyg8bjhiQpO8+kFLn5PNhii0F9IHckPq1iLqLRu1DqD6hbQWTlwY6BirqqZGLCyTT4K+2XB+pD58uNZ3ECAtQttw+hQL+GauIC18t8pz7qDA0MuCVTUOQQf+B2ska+EHnxNc442TwgzK5v5W8D9tmGgIgZuo0IxLdhkGbzm0XqjyLs9ILj3P/O4lReMBqdFMjhsOMsJbauZQyYW5WG9+sFsFyaMcpN6RoF9FoAZtPjGmxDdpRzgVVrc0Cgc2kpbHbu35x70vghPyGarwLfPXCZDUyZiuhRUzVq6k5TssaFn5iMonytC5LBvMDnjZpuooP9frFqKPqWjoQ1mTV/OS97cCrue+STfr8gNTVeokeCY/hKpziyBd5oWRuoUygYoP5XlMFjPDF+k4rM88bEwG/cbFy56ojamwas7Mdc7LSLGiXPt8qbsLTpWJxhUC8JxL6D3uZaNMU8mTlFlm7PkMxyXBoF8K85lHuwilFg1vOzZPZdGPU/sdJqaSu9sHgjcsHVMkNbXD6mJVRLRPe8eslknI9/SToyHEjmxPDyiHy2CuqVsAeR0c1tcA7+SXaBsEFG5JBFbEmdee68+ifEPz8ZIvjb6dQuSMcSpcvDnjvJvWPE2T+YAXGPzYl0hns2LxPjGK2Bvl/97NYsd+Y5Yild7NgmJJ1gl8uJYgc9syywoileUaDPgdvmB/RrULefVlDCiF4moEE4lGn3Fdm4H8L+0hWWWEvM41OCFd9woLOpa3pPcZVTNT1f2xZYWv/XAZiZAAFZIpExW75zYzQWLrRm/DpcFxRYFvP0D5DFy7FxJrDVnez7F+hhIxWbq7fMPr+/f0NugYACP4T8if0z39/wv6E/4n4E/kn6k/0n5g/sX/i/sT/SfiT+CfpT/KflD+pf9L+pP/J+JP5J+tP9p+cP7l/8v7k/yn4U/in6M+/P8V/Sv6U/in7U/6n4k/ln6o/1X9q/tT+qftT/6fhT+Ofpj/Nf1r+tP5p+9P+p+NP55+uP91/ev70/un70/9n4M/gn6E/w39G/oz+Gfsz/mfiz+SfqT/Tf2b+zP6Z+zP/Z+HP4p+lP8t/Vv6s/ln7s/5n48/mn60/2392/uz+2fuz/+fgz+Gfoz/Hf07+nP45+3P+5+LP5Z+rP9d/bv7c/rn7c//n4c/jn6c/z39e/rz+efvz/ufjz+efrz/ff37+ANz81X97X088cRhaoFKBbZbYQonkHqeldIsaTh6loAv92dkipqWjXU6q3/7ZTGWsCJg9QXrZ4WLUCohp
*/