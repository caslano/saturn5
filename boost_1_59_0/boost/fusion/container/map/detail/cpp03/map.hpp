/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_07212005_1106)
#define FUSION_MAP_07212005_1106

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/map/detail/cpp03/map_fwd.hpp>
#include <boost/fusion/container/map/detail/cpp03/at_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_at_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/begin_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/end_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/deref_data_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/deref_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/key_of_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_data_impl.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
// see map_forward_ctor.hpp
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/map/detail/cpp03/preprocessed/map.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map" FUSION_MAX_MAP_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define FUSION_HASH #

namespace boost { namespace fusion
{
    struct void_;
    struct fusion_sequence_tag;

    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_MAP_SIZE, typename T)>
    struct map : sequence_base<map<BOOST_PP_ENUM_PARAMS(FUSION_MAX_MAP_SIZE, T)> >
    {
        struct category : random_access_traversal_tag, associative_tag {};

        typedef map_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;

        typedef vector<
            BOOST_PP_ENUM_PARAMS(FUSION_MAX_MAP_SIZE, T)>
        storage_type;

        typedef typename storage_type::size size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map()
            : data() {}

        BOOST_FUSION_GPU_ENABLED
        map(map const& rhs)
            : data(rhs.data) {}

        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        map(Sequence const& rhs)
            : data(rhs) {}

        #include <boost/fusion/container/map/detail/cpp03/map_forward_ctor.hpp>

        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map& operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map& operator=(map const& rhs)
        {
            data = rhs.data;
            return *this;
        }

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map(map&& rhs)
            : data(std::move(rhs.data)) {}

        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map& operator=(T&& rhs)
        {
            data = BOOST_FUSION_FWD_ELEM(T, rhs);
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map& operator=(map&& rhs)
        {
            data = std::move(rhs.data);
            return *this;
        }
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type& get_data() { return data; }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type const& get_data() const { return data; }

    private:

        storage_type data;
    };
}}

#undef FUSION_HASH

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* map.hpp
ojNXIl7lAoVrXXVgWn3bx8/2x+NJd4FsktGRRic5cOLrWc05rY5St+a2GOnVtO1yedYpK8K1WBwbmCCGVUGiYhRHDzwy/LWkk8vSWZcVAwHFG/36Ifgo7ctamrShkUFSSx1b8PZID+4Wu0r/Ipyn0LsMCe8y15QqSvrKXQdhy3+JIJLu/5lGrMLWMkk77lHzRsuo4M34IdDkTDLJ+A8KUPCALcbmpWzmaH7JOlFhNeN7+KCAs0Lwc6JBezrRdFbjKrFu3KXnZm0EjsIBKjOIufXXTOxdVdemHvKPP+Fguxte9yVnEtziG5DuBpOv1irgAv0D3aiJRPqzza7LCS/vykasCFEONj76J1C3HAk5TK4SYmnJETKTwL7QZMMdDGTjUXgfY3Zdr9iQB8ZWbOALC5VbpXh4+pIuUFd5V2rIPl0snXW2uhtsYihEg31RE2O9IjSW1HJipBjxs5R3i7O4hC77Gd/F6J0t7SnPGssrJ4xMkjhWayC7ihLLgqAlXiuPUT9Gi+5A8x2V3VZvW6G72AXN7VBf+z/qWiHSAN0Qxx219L+vlegvduj/xyLpspSlhYSv6yxL0fUD3DMMdTc6ZMn5gT4CsyWmLsl/LPq2m+6Wf5yxBeu+YnhbgSrAx9cUf/nJFc9Qf/k1DLjSPcyUXvXjrkyMOEO0ePLuRzZNCTnjBR2WoAnIW81b9VTB2/LjZ86yjZUYGpDE30yIP3+R2tBWFeoW4SaGPIa3gsNaTrTxccEIZP8R8EdWdhGFb4alcYdUYe1sb58GmzPIV68STgtPW6RYJIITgWj+rWR9TeF4FMHPUFmD1ZUBGAFDTrLs9tdHGj19g8DCVhH/1zS266c63Xs+6iHr6iEankN97Au2nnq8gWOpQtnwJZwLa+7BEsCLyHWDf5KAqoLorDCmPpX/KxEY6rPlhsYvox9M3suUv+8bx7wTx+K6XDHwMPggHcau4Dm5+lf6aX3a6Se006HwQfmzUIws1fNegdYsk1bbbrB+Nw7+PQHnt4b4RI7Tciq8/hv/QKCCVr2CVvq0ubTcGyqELXh2bLGnN1c+lNBCgpMdPDQK4p1pmrWy9hPq+odDq8iKdgC1FGAmFYwdfcHT3SHzsCM8gyb248xz0HSNx/LHYD7uJzcRBJcjkrMP9E3pngb2PthpNR/U0CtNzQwN0MtwtaU378UwySkvJisA+TEHHuVmDiEkk8yXHvTTMZqfrhUcGZyunszK7l1tP0oc920e/QyKDuqBhlZK3XOnJ+EuV1BHRdSI72VM5lroX0vTzX55vYzyPksBnmMHyWu9h1/4/gtO/9p8/gGxY1hlQJOcuFtMJiIDqRNk6w1He1pfC+kiwbokhvYS15mXqz3Wk2qmYgtbrHcOa7XWwR82wVB+L2L8sxXoMBryhl8cDY0TX66mbGtJtV9fB0Ppb1SAo918V/EU1/ovcK5JDs6K121imFCVdTDArc2u8fhHzTvh10/Cm+R88cKp9vsttng9TzyMHsl41eSV33cTJ+OlASrGAAuP/+2L8r/Wb09U0VsMTOxfJr3zl44nkII4FdRiH4sfExgmoV5NUvCc0VAonP8bdJcIfHaBeR4hbJu+mQAfhqBxWt0rWuzgD9nHqrM9R4HFeQE5akWqZeo3JBL/8ZAlmG8nX7pdln2rt2kmlrxVwDh2M39TkfQqIgmDE1bJXTv0Gz+EF+89Mit5gpUk8okxppU3MqQaV8IYOw0vkbs/xGoHc42Ff4v1ZRf5J9X9BqpikV0Q9wdYav0OEGzn/jZZ9TRUQJqnYB0WThxQUyfjqK8N/BGY2t9yReN8wzgqoLIOutXgQLGT29P7+zIL450TRFhmPMUd7MST5TxX8uwZxdOZMqL8PZ9twReTnH2jkU8AM+IXRSskFWQTXoZFOY6/cDiA+XJ6AMYkRzVG8fWXAOMJGhOFaJ4D2cTosn3CJCTbd5HmtQFWziegXFHWW9+WZL8SVN2YyB2OdGMfh4A4h3Ey20XPWha0jiL9ngJMEfelAsUydmLfXVd0vKVne64c4zVnqzlFu22I9q+xCWg336HEgXtvF+mhzteVgoSDJ0hwVI17YrtY5QzQWIlo0OOhQ5PtIh1UDGyO15A8I54sXODNsCqN77V3UUVpvz/6SNC8uuoTRNN/iuPrGBqvezWxgroBhsLRzxtHy43tcz9Yn8xLG1aKGFwnFEbk9lt7X3DiVBRbkkf+MGwXPeped0RHzvatlrRNPTz4scHdmcfAIQgO0KhUO/ZdKaoyaLpNcCj+XC/48k0TNW8eOcocbmH1CrzxBpj+44ehLgrmaszZLDkw3JlHcM54bn2qK5vIrF1iqUEXxHaeAk1OXMMZaUabUYfBMwxfPQzw737bgBgqPJzzbw3ayY/nGkHxWmZYS1bxJnpN3BR3pmaSSfG4/ST/qeNjHI7jSKMlldFfayGHYXTg/Yf9/mngUI5fC2byh98lJd13rXjjpL7pJO5CcetKO5rE2yDLrjc57e4tAVMYfrNDa5TffbUylmlt1FV7UrfPTshJAcZ3uad3TE5TZIedlUnag66/ijECd2tBV4Vy8zICxxZ06v9Tq+ut5OWvu7/Ak5gWbVlx/r9VQUycHhfETmaDH7UscKyJXN0LSjj74glZIMeJKINGdn0XtYj28xWD1xs63KhArPUWpCWS9/NxFdaMmtjF9TjcI82NLHb4gFvAi0oNv1pQ551LpZkVtyX4B9wzv5g4W1XNXiPH42ldzWNNSaVg//5HmKa2A+1jXnC6tOYC91WKZKB4hpwfaz/5YXwTqdowZbeJpJb+4/KfMky7c1nuN6WrX78uIHvzGIdeNNTHmc/aNtKUoSYj2ZuyTV1ynjH9MVpnHv0V+kvWk7X4vcHsw5PLK0eHVQLRtiXc0V0u+96rX2ddfM0dtLSXz4qGHML1X4UnfW4elAXH+yZR6nrixuSqh1728IY1X3Bd4VQMZlGqlaqn0im/kI81p+4zndbTCoT6wOBRemc8mkuv488CGfdkRi4KHKXiksGhqjjg76mn0fFdu/V0A4GQx0qvqOm0Z3kNVf0gHqh7q+43995qria8a0GNImxsj8WRUuKm/S849F1tCNL5SW0d+ArsP70FxIyW0avXnIBCqJb4VwdFMBTSK95LcccDQprsgDAs7uCoe9wzwJh70YDVRPXQVr/TqzLroX7M9w4+j4CseEBTS9RPA1KyvCo71MC71Zwlu2gA+PV4QNScNoBpMiHeyrQ7403L1U3Nj1WlFUrDsl43VSKsUA9u5vnU3T6/6TYf2XT7cL0q3mqxX2ZJjS6PaBPCC7M7+aSU6Ix6V+NH3Ts33pIoyrxrOzj/EDCw1ZWNAxz9Pul/d2zQncG+rSHhaCNrAop/5i90LpijdHazsdKrfSr+6n4QS2rpxFNVonvpTKs0Z55RJzjw6hyYu1kx9QDLVdmY1NsdrJPjWXFCx4crIYMF1MBeS5IUQyjnmaSXBr7SnkdBUauMaHgN4SHzMERkuwgIukhuekLvmSjOBLDZXpduhnXdvcfKF00JA06uwmpok2JGUOdre0FDykYM/vQ7mIJNxaRfynFcVcoZSu4TDxTi9Oy+n4z+s3hdHJ4VNCLaonnGEVHW7L0itJoHeYZx0XlX09lvUmIadjEF63JaEWWnubZSjlsJt3E4ROP1FI4Mp3VdoHJX6HW7uSZa//pAIey6ahRo6GNQthxGBPPz6JOCO6HXL21SOQVeBAf72IAwDFiwJuJDAqxSQye066vhzHOPdMa5Fe9g4P0K2Mf7sVAF1w0FicLLzwctTG5F75xo1q6G1cjvxf2+FPJ1k5QAEQpsD7jfQGom/x4QxeI0EwdYNpZ+151+//bCsbbXPbawWffbvJwnWYfTo174/MOfaZaj0Dpr4iscMIa8yumnownhvbA3+bex1sQIKaZ2GUMqe5vzhc7GL6Ra72j4vs0i1viabl/g4KKVLQV7n3xEuzNGMx1fO7mJOWcXKen8DPNVKjyknoXWaWL140MAI10um9tTRwm0x0UOS83UHSWeqdKx08HRTO0Usz5Ne9qMXvai4oHM3TgO/ypilPxJULPOQr2xeGau+50yU+qOFx6EB0kSsvGsBZ8DFN4K/dkaifKzJw72v74BaY1+nrVlo1i92vqs8/Kzx2+BA8jF1/nWqHXJK3b1dTsFpYtVzMojoMRWVy+uVWF+OLAQ7eBz9IWvkChtsPHDxVfFTz1/HAdyunvWOIOJCiNWkxyi7jbzq9wFneWB6n80KxZL6x3PSwGfBQrl9fDFi95Fq1UVvnxHlptIaGkmmiOEPVl5BBhrNNNs2S/yHZhmBbjpky+CpGbm0e9aPq10H71vqfSwKv7Iwtb6hfujoIU2IK7x9VijtiY20DPq8hPEWvH3j9LUP3mZvyIQGRt7fPkExW8fJJ/U5Fp/GxmwgJnTe9GN+e9rXq2dyw6cLAuNKW4JFYJGAjRKbfcXIdbGRCIxv9327FTq2+fcQeYDbC8GadCDw6Jbd8tZBoyW4Z9D94jKqofdM0bmP9w82qExDNG2OVeAxl/Qbmugr5sYQNo4KnEYimFI8cnKJ8jTgL5ChvXzVjM62dOqmE4JOxUEYK5k2jqOfNgdFKkKv0gOet38rkVyRJsIId4YhhAPFncu5xugK5PUW8FQd5u86YLa3fFzojrY825pWQ46DdruOi6KcSnNg1gGPPkMccS4VLpX6XlWtX+P/WLZxZxzeq9F1a8lh0I55VwFOJ1Jjv14Mfx8/PnKR2D3gNsHwd0/RxIxJdM8fZfQoUZX6UTkzt5KWO6AN6uK4p0L3MGh1ojVy6sET4+8iy3Ix4FK/UTK/THrLl1O6qSPV3VzSNrn5F5iLaJjXCynuYv5sldpk09exGh6s7uS7QXPlr+7pT66r6X6lmXPwjHOqXgsgLl7081Qcb/IteALZ6A0RJqJp9xxVrCOz6nDoHf+6c9IX6o9b4HMeIzMOKOfUencwxd6Ey4UrtR0OeeOACPXd6GZrcF1quNTX/Kt1L/MSgq0dLOc4ICF7FWbY3ZHXR9LHCWrGVzUlufCFZpIhUloBNzL8n4kLYRt+UldiXzqcTqxWYOnKLwtvPiR2R/7FOEk8H3A9GypP6LqEEWtLNRz+GRGG656Us+si4qQrdVZHWBz+4UDPxhuse6ulURT/3EPHLkSUEA8lIa5ePNUYMUZtg8Zf4ICtz3Ig7+s/KAfHTCGAeKDrFK/Ufpn22ZJPeuxHoZ1tM02EG8yZyHrq16f0PX7uOZDTCynCGBan1ccX41zsH/w+xGm9FHa2cJi5IePONwpHAgI2vtzT5m753tq/nyfsCy8ogBChJr6fgw0uJFXn/bb9rVfQd80MTwdMP0Awwer/Fx9md3d6Cx/ubA97lxasECwP2Gc0/7uUdCIWEVu74LWULHzjSKkclG/SdcKwivKGjGmfXOqAAMs/NMmylraS1iwMZZovqi0oi/qOHWNzadawSBsU1vMzHYlFs/fFM2wYghJwMwjQFbj6+srR0FrDLdXVfgezWsAfJ2ABnfQ8Vdx1mewn7b2H0PJLMuaSLUOGWfDMp5wmlVTg2FEW2cJCBw7tgEJ7ADfwDFh2FHZ/xooWqsigOvdHKMOeh+k3k8Cg1uP99liMW5Ld0mAgY26gM3DKrmngMDvZiGOjV86wQ43fkTuY24oSs9BieSnq4TtzGRpgB/fBb1q6WbYuJco2oMMJS2y9yG/5ChHhpq/524z1tw9jDyEcxQzM1AQSNV1Df7W4c92gj1J3sxKKnZXLm7Y4f2q9VF/Db1RQJAWVusu3ShvX9Ya2Y3b3EI0GnDUj9EXMmerssT5nrjOHvM/5qCzJ8bcblSRk9Xe+FCeq1uZCBVYwosQB365htFZWaUHBbqb96/ETr82GFopaAXSRgz/rguB1VZ8yh62cCazoNYEcfxIFq6bcLxkGP1c+IO1g31M2FgBMcKu+spTxpXTeVAw+ulxjJZRtHL3IfoBc9cQzMQ4/5XFw6xI9pe3lUllRkSU4zyRVLNWW/Nv1YTdiUbeKvf3GRlQsDosndcwbKg/eY6m2/pgMUMk2NHYTQA3NhWxP/IdlI3bDp4P58V5XmRG1VxRXnuBXTPOa0gnLpLIvPxzaW1NuHBcswcyBl+T2oG8rGBodkmbm7oEWM5a+hhZA1WrkDz6ORLopm7SojYbkFMSZlRqAYWWt2N80pYRv6ZeXczG8OI0TzwyCgvEk6aVoPxOa375IXPvUyromsctjVWNfmkGvSdY8vHeR+R982XUraRMKyb4ZXb0iMheBLjmGEQD5eRlelVhHFem9lZw84Xectbaj0rtcv903qA5Xdk4aG9J31qnRKplj06ZukQpNXMsIPso4sRQeIwbrk1cH8O09T3IO0Osj86qEDL2bp21gGF9zj1xLJWIpjHxsxiaEJnbASaDs4Bu/T0Pu96hm2qvirzOgVUBM8LDft8YOmbhfHQo59VWLE5htyRUOOWZ7iIXAR5SxbioIVdIlwQwv3wuB2UaD8fcBU0hrF/eB7fJFvlUbh+5qtcKetA5QI1ksfzwJ6gdIM17iQFKuPdt7C3UwRI8ROUfnBzGGmWFnFv62zCJHO6p02KquMNkRlQcaso04jlzOf77h6w/WEgcC4QI6n8419I66ohf5opfvhG/AIqf82Jq4JMwTXqdhsUEfXmnC6m9ZdnNVBrBtvcMIWycdMQshpMMJI5C0pK0GXH+Uyyqoti+sSIkCi12GAe/7dFqDSHOjmjMgo4IJ0szy4SUw17DqD1/zOcSwLqMix0JqdogvhRUr8QNX8JeBb3lBhRl7J4/k6QfrIvZavzdsbdMNpuT/M6aLe+3KjuWeBwUhF7ZFC3MVd+IST5Qu6ogjsBRO5/UlNzU56SYL2oedBaiBkMJS67cHIJrc5y9gZLCm3kYxRj+1+ObUzCNiUwBNbtPJHQFavNr5Mg043rcgHp2Kv/DfS0+f4URB6U98RXEm3uI+wWD7i05JtOGAUKq+eZmFOvIgfCqzE5I47fUdgH6lp1/3LRc3yllYgYMsLkJ4sv3baDJi6E5XyfNZxq1JpraTEomTJcsX6ena4gIuDNvn61+oteJfxFljxUvmHtTMHjfcjT+omPIcdVsdcsyXA1EzO4W0O3W0fiZ2QH2dHnzQ0NqWO3H7nqf79NCGjMgaazUfhAfmbzJVidtQSpE7+yhkDzab81tain+dWp6suaoqOnHuV+DQC2Atv9qJCqzK9tpaXPlwWeyswiYXlGhKEdc4hVb2p5IwaIvq1Tgulnt0ZdOKIJsMdTLZZkfw4tebEb+/Cjn3erXJ5vc8cSWwj99BvbAIdUwV/dLJTSeQQKRYm9MMWic/+PYC0nSl2ydtjhk7RyFrO0rN6uCkVc0J60K1SZBW6XtCbCDNzKozx0Of+vY0h+mvwpyaYd/JsNlEmBclBUGPpZOS6WaOWmWt+loNkOzi4SMAyT37x7GaS276GJdzliJP6IVHW4GCBSWMjkwSQi42xsvDR5Zpi22It4TtuyoOOTjMMm5290yA73AGO1EhMKtJZUo3Elq7aB/092kZWCt/iwv6hS5hxRcgsS3u6kdfn2aYx4/z/ElfErqhZA/i4cnWGBNu+W91q6H5kFw/MIcY8MVUwNE3GbY
*/