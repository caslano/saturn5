// Copyright Daniel Wallin, David Abrahams 2010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_IS_MAYBE_050329_HPP
#define BOOST_PARAMETER_IS_MAYBE_050329_HPP

namespace boost { namespace parameter { namespace aux {

    struct maybe_base
    {
    };
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using is_maybe = ::std::is_base_of<
        ::boost::parameter::aux::maybe_base
      , typename ::std::remove_const<T>::type
    >;
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_maybe
      : ::boost::mpl::if_<
            ::boost::is_base_of<
                ::boost::parameter::aux::maybe_base
              , typename ::boost::remove_const<T>::type
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* is_maybe.hpp
4CghqPNAIP5xySiXgO+UpBtTyxZlGZPID9Pm/jp2adWNPo0I2aXsWpIHC/O7ZHRwLW2PYTS8Wzb+9znPvhZkwjKLuqtXJH563Z/WOfVhHe+yGVnE4aM9+CjlMu/BY9fcFA8R+Qj0Jk6uR5QJkUJ6WRnmf/yFKZiv0B7dz4k53bqjCuQywazq2KMICQkOA5kZYcQm+OM9jNnEMBDiaqXsa04uUnm1NRjg027qxgKCNGwWrILH8MgVNswmxUEswwCvSZBDpCW7ksNM92DMPMWfreYxz9BJavkisEE77ZASs/xiGrvXEi7OkAcO9AJq+YTxvHX1p2CWvUwfppE1syduWSOHopHKUI9/ZxG8YzUciWzNqAOZMgA+eSUGKvkHbaSIYbQam7Mw9RmAH75ksQF8OiM7QBAajeXIi1270VDZodNIixHp+rIVwpZHjyTVuxv40kb1KzWbJSs6D1VaCo67BmR1VOl+IiF90DKWpC9d00EHh8br4waQyGbjx4hyC1b06FasaEJ7NMOb5XYt16h47Glj2MwNrL5SRMrU8TnaNkF7mVsWW2tDSKhDelLeHw8IaB2OtDDfuR369nuwVmvGLUZGNibxzpnZD56scFAdxhPOMgpkp/woeGrbiSCFmm14Y9uY03d09zLC02WwlrSvmE109ilsDlTfa7idGAB64eYNnf++FaLjlFUekCoVbt4YFItcLN4XGVe531kkU6tEZKT2d86s3d2hfnQDfNxvLOzzbvs2Vwe6V3bfd0NTPaAum4/aRM7HfELHoOk5gC53LLEoUSClyeYXL1X0s7Sw0rOYJV4B5rfGGWX0IuSrJkHcnYup20BuDEERw79aVsAOhCeNzWp/CxGvoKWopx/aIhEhaFbm0XTxc72/5RHVxX4nN+MYhrUB+D5U07RaUUtrh6HmahcRBZQly97UFLFxyBIxL8IWI1amvh5zhg5Lh7eAE9LITOij5/VVH2RSnSeD0Oqrd0Ht4PNlawWnfLfkziuWcoafhTgRLaWfpQZQsqjvSR7SU7dXnqcMA3ib8yzWGOXWIqPtDH50vu6Zd64c4WlfC1zfCl7HUpiA/RGc7VKznMGjpiYTdP7rBiQRRDUPFQ7vHwhr6A469kUI36MHO+sEIJo/CfOwFlws5UPo/nZLoFqA9v1Q60p68oaYWggvGl/OZF4VzFltfYbOXXjEHQkzhYQ+J96TaluNSrc9W/Kx9U5yBx7H7vcQwPRew9xJUU3dT9TD06ePNfSvrzDbKvqLrApnoX5gxBFIw45PzlHyCguPQgmhT3e7ZGsp5Pli8c5sSSPBXebRQyQwFTxN3pAnTAgIs3XT+GetKVR1qISLny1jOG7wWiEo6huIBGmkz/puwFYSM5y4GfqEcf+SccgzsIi/I4Ft4kIgTuwlsr0Y8Zi8+53W+ZDK7TKfptyw8slWG+dyRG4+Onb89Vn4feuQOOXIbO4qtzFfKNFI2RW7eGpsH4ftTKG9u4d+SlkT5TsDfWdj5mx8iYdW2MewDmTdTJ+Up+CCau7d7wLUz/9ISuAynwzOgrMy+C+LsjR9aOsLP183u9Do0XBZNQ94E5csn1jPSTpaTsI+kt0nsBUO+T5S7YLd17E0j9Muuac0VI9xhMtzi8pKMMDYs9JoCkJxmVa/7QucXdzCnDNb1KpmMnChHZFSeEU4iQOYhgaydYiQz212p5T2Du5lv29usZstk9uNvWRFjNQhjVgeaMIe4z3J07ERVDudVMr+dupcdi5IIVYOXE9ojzds5Gzs7vTac427mEdT3JxpfVJUIYyc5/YAq8kVNwlnb96V3yJc8nUsFOk7kkg/OixqCLgO12W+fwA5ChhYpz37HwXJ6Ms9oOXe/d8uTRkMecA/wRKGL6Z0UX+XupFp8HpOz1u9kDdf8sRbNHLrUhFRQJpYDvR6ipkY1VfgPEtlFBMZTZ3L+TET1M3pHKqpUKMT9hxxQ9QBw1tsC8s4Y+87u5v+EoTC60DuZ/6fWUZpbrHEwqXU3OUyv5sHzE8XVjfosoTHm46dv/rOzVJGd65IFIO0AtqftILzg1nGa2v4hdGkpugYRcdhrlAHZVDFDemiqUbAv2ZGcooRCHqc1N67ADcidMJdz0XEB3c88NrTQ5z5zS/4KzV2RkMXckMIupY+PDc+naESIKakfY+YDjgIlB6kQle2wX1hMvJUsOrSpB/YS+vX4PBqFIsoPNlBbQuH8Lu4g8tz7aOwxC09UP4ysW865I6OMeZMLkSTVbHMNJ5mN1wAp8zvcGbYH8+4ZipbUQ8x5ydguz2O0lbi6r7akmnEqi3GtVyoXG4/FNvoUyMmWjJTId0eeypL1/lchV0ulSkxcb6avbIM2GZN/dTNlIfQJ9falr7k7Hk+q7gSoSwmKiXSEo9aQ5ux8nJq0y0XW4sdqzEYW0qXq8IbM1wI/Gu62ZH3oHPRfDLUnrvwu86qvBLMzvD7LkfSGBlFwM6Zmo4nwhcD1TjcEYqfxK2k84aECxHhu/C9/W5DSOT57yiX8rDD2kGOuj2D8IWmn1CGSVV4UArmpWW+6WOq4Wb4OmXxKf/qzeyZjXtiTi6Ne3T9rWRA9ZjeOBNq3b1wxFZDJupB0248Cc9lH9YvjEhLWk0nKVouPM6K6TgVRrMyFNTDcS4uHKDlS2tCpKtVC+Q1wVJO7Pv7DS4g1QhTFhEv1YTDXpQOaHISHjvyaev35Lm4QajiZaoHWNw87xtC9QNZJISM7+VtvGDhZvnbsUuWn9vya+YcrPB7NgR7j6QsfXPFMlMKdtWLo7DaVRPiUhonnVCLwUasagP1CS3go1tk34Hb2OKiL6aFlwQQ2O4ZBMr2PXKf3xFPeh3UV7YfvZTZ8OIDe/5ZJiVV9wPXgISYRi4mpl6fxrX6JLz+QQbFq1zvw0CIkTIf+CNeFhqcfrCTT3TbCWfc/jLgPDUNT9eAWwLft4BtBIaVO/sFapv9J/lRL5Y/rV8HVPbvO9Af6Ic7I/y1q/s3rwV0nWpjeElNcrW6bX6NRk6z1FmsmoExhFZabkBXbiENGjBE0GTMLQNeqHBcT+FrFlr8FHLM77pOk55UI3HUdw9hSXm3ybl+7NnXoVKxHqqceu7ohX4OUBwTMDKNG6tFYm08mcIP+uiT7ZVZRUeajPqHbiUUWqpO83Wej+ezIytLS0b8seO2HdlMWiG+52obieBBde4VVL38fzElkK4Vm+sxs/P6s3G4Mz8G9YWxHTpHcgZryJqQXSQQzIrBTz2wGe9WH4v0at9AIMignLNR7315c3+9VjO6PlXPo1fJRZU1qGmGnV9GurUsSL4uxom4ASSpH6sNDulKeXbj08WEAHjQatJpnpYTkoffQRMz26kn54RqV+1IathvHUUJfMyTcnJGzbbPdXNClpImmvVvT+C4QX/02rPCxjRGm7IwXBFjHkYAjV2bWo0HjhnZTsLQK09d3cI3cjTKrdvhxy11rIyOpJaGZkAiDss/G8q8PtJIK83jIfQuIFoVA1CvkjLHT2UyTp48ANp/xkZHm7OccB9h3UBGT7IS7wiiiJYnZMmclL/o8zpfWxN9gTDVy53v7Lh+ZM9HGY9NoE2uyesLfH3c6d7NlnLLfTW/SVLzo266kbiRBtpT3RDMn/lPNdjD1w0d1Z0EYI+858W8gFAaPtpIbXArcJr4lyepwidqDf/2fGBV3f+zzAYwgCjQp9fVfpx13cDc8PERPiwX5Gp0IS0uzyZ80knR1xoGoF/8TMhgS4vmeH9dw1RO8l6bAVWjRA+tZbtEvPWYmJV9spbawx+PWwGOJU/zO2Q1M457TIPQu5wrYTzCjmIRcyigGtICg7VIw88DsA/HlOm0MMbPaQvW44ONJohsEcDH8TmDz3O7c6L/QvZ9h5HKX5ZjEqhwSO7q68Vhl/W7rv5tWOhWnFQ5D9Uit2FpEtX49g2Ml01pXFAMA/7diDzYls/motZgjIY28s7/vPusear/yWNduI+2JoY07hPU3LEor25KC9VFp8KJIDz8AxbZTIJFtHya3C583uMq46tXbmw3t3QpsTW+Ixjk0yVb3oUbvDSfg7+JULF/C3KCwVIMaDb38eL4dp9Id4OfEmNFhlcXx7igTZXMV7kKA2aNS7MM5PAWfLkerbVQjs6tJDtszeHVx+sV5u8yWWuxHcgR9eq5XX6pi4I8LfSl/uJ8gdVhG6fJLUGVXX/aq7eqdGmxnJ9QacZ0liVkk7XYcNA26KiZK+H+GurWEIs/VoZYNaMRmWowNXbXLd0GsEFelXn5tWJ54EtGr9gUZ8CQwT3EoG7ORePf/we+5HGMsn6N4mBPvc+QOXjVwPSsz5yIPWAC3A3LF2EHrbNha3olALayM7FXzHOsi4R4ttARBFykshemjn0jdVVc5LsJcagOiiDcqOFqFnL6ZNdmLVfI6Y2tS6BB8OHVzewZoe1rc+8Y6NI/wb4saB/iCZ5/W+jKmXrAfV70yj+YcBZ2ceWJO9ftahFI3A5l8qw014UkOHibnCBGx4MdVOPj1KrAUx9sZGArE0b1PuuaPtvgurGjmmDfz5tcBpccZbi3NcePtFsv/Oaor1BdnGv8WP22QpsbncC1lU2ZMHhdpHKnsYkVxjMRruxwOKDWAmQBUG3czZHUDJhu8ovKKYRiDsHC95ijfdtu3oaqDbTdSmwS22z+oZkoGjuWe2zYUSbCQCgawWdleakC7EQM4+cUqe8tesFgezoOXOW17M2/XpnY44gY6gH5MYzD/rMKe7y3NOac/vXHzDVrTvjUK5AAthl2BSMQRktW3ghtGOkQZzwoOwCYepMU0Zz4zWZZHZSHPgtkrSiFU3FEZNNwLgUunWQ7TPELAbl8If82cTJtq9B42IKJfxb9Ogzt3FkLGuKixIZMnwCrecx0mOeYEZh5WfMMii+KccB3OC9blRyBbJmRDMXCrHVp44DbyTgbmS4KxevCdv5zK7wsXiPco7jbnrvjYwZrhGw+t7MbkXDPnXd3pmbaBirr+M49j7MnQDyiN/EY4p7e91N6xybMQgdMMHS1eCx8vUdUqlvVlLGJV2S4Xh4muIEQTORhk4xYrHmaDNJK1jxeT1jCqUSui0IJ517D2C5JNqmFMyPELH4jjSWZzRPOpb8oa5lq7S/qTt6BYOpReJEcccWFklXcjQo7Ft1smU35RGHQfCK27td+9AVrsFPkZc0czOjBcG2v9aqjHChiEl9V3OghEtgcPR+GfUXy37yt2T9RxMz7dvZt9Spv/2SenuIRC6dFiIrlH9oIw/PRVMck6Ct7MqsHYcffXXYhE1N5xr6TS67pa/ZC7ULVAKZKqMwnI6XHyh/5O0P+MjXBJq6tFtsZN2b27u60HX/cRsPZvuVeRy9nXgsV25APPj5sGeF8RcJehPnnf7nGxqi9c8IuE57aT904LXGHeoTjEV5EJ+TehcXScUFL93uLPBke+5jPZi/39nEiv1BtN6mGnepx9pOmdd1kz0A+RKf+Lfa+UbP2h4gBPeQWvpRoIU1t+Gc5peYbkVBJ3UIViTNhWOpc/OyelIHI+9UVXAv1GrERGWW1JtRXmQPk1gA6k2MYjpNqep8c22bFT3hdaE9yK7ohJilDwXeCawyhW44xrYbKZMU/YXjwx3Q4CbB4dyQJkK57fnBvo8mVB5wKJ8dXpM1OQ/BlPnlJ66x16TW8K/gRaJKYsDgmaYaKVleGGiBErCxlrgyJEc6qxJx2Wzt/+Zyiy1i68ABKu6d8vRm7B42MHpdwwxQDiJDSNmISrAHhGmMcCzPPyudyGCmkFWAr2q4bEKtskpxsENvemg3/b1j/KgBpkZ67qw2bRQs96IH+gXWIyYCgwu5E75fy7nJrOJ9vxFx1Atw6lBYb0geAjn84gMEN0WR3KiYYbhBGHPXLd7m+YBrQuCOefGsAjAGu8EiYkg2icXtaRqlRFS/7OPDsHJVQ6/7eOQZnUFM0i9WEvemastYzQp3x8r3RkCSJFCmdPr07X0Ix10sB3ugCj1fpzILOBw7w1090Yef1Zgy5mNv9IbnYy8Zo6eFZyM/U0Px1NjlHR5nOHzkNKXvuyt0Ro7xgDfRHZuWUiwzuayX8jovET6XGFtJHwXJtnFPnRsOlm5bFpZ43lx3W6wvWRdVMQYuCvSfbzOu9M9MPpCJdYqXZODlvQ95tMUSsGmxrZJNWdCCZ6UnlhxoTGTLUuY71kDLH+V1ZFJXnOUUi1Bn/soYhAIf42oUNFxJdPM7RK1ygFFbLhw0VT0DpreJBWKkujbvxXUPS6tnv0zk4RzcMTcVM5ia0zBXeQujMFSUn8UxVBwU4t9TrRCPUau9eTuMG8+m2tlKRy/ZbBLD3I+tGSVWmcuPGlUzlAAQs+9ODlAtQeeN+anniISte2Q/AXtTcarvUfQTdtxeCtQbGXG0sbMGsPX4LyCOmuR0MAkp0ve22rAtcWvsIKYJy1TtbbslrvmS5j5JoQGaE8YdVH3fxxUMM6aHZCdId5yMUVPyDaY2FImtD05WhKO5tWjZfYmi0yItuS4UQOZpZZayGiwfHex0TtNObzg+zOuPyyEcFHtjlBKdAqjj+dDiRA7LjG61XmOLcfFkMCtUri9QoVGiMmX/BpWvJhqnsLzOya1RTjO5vrwORVz5QUWV8Wn019mzu+ZqU+VgsAjSO50Vqo1Wv9m1UCaMfP8bNSc++z5eG+PUWLUaPpudvHZJpLBpZcYMQkT3hIvgkqAZENiSNR3FoD2FclozS1/2Qu/5h+7oaiQ8A8gVsAKZPB4WbXCbEQrmvszjYXwvWEtbvfen3QKdvS/UnL3hfNS/L5zFb5RhuOZlcLA83jcuV2AipmqHtMLpkFKNAjHYQLZKLuHcTpaLd+RMb5N4wiMX+6Up8vvU6QoHTrEpog5/eZXCYiKIvGBeIuQo8axIyFHJqE0xJ99LFXkVpd5ibarGIg1rFjJJHk2SFIpQ8ChOjlMeH9BSOI7GWGDcF4z9KFcGMoGxDDNsMSriD0vz1cDNhkr7k8+whMsWcYfWtLs/0xRRuGgF6oSH7QqguE+bqU9wdsaKXSQqv7Ya5Pimit7pCLGjh2gmFG7EJM0ISo+oRDuZGootk3IQvFLDcCd1i6YsiJrpmaJl210HDBlVTWYZq//AWrBDzVTXbu/l0lmmWINmzcytAqqmMzdtv9gVgvX3A50VQZ+MQ3QXL+m8WR6JsDLRB5XC7ObNA865V+/Sfv4ObH0GaeRvukh6veBIJPcu8Ywu9Uz9kbXardoc3Vhthet9tXuwZdpdDch1ghkD1am3G+hhMtGLR+GKHUDuMFwXd3vQ6sr+8wyp29dYm1z5IyAldsCV9ODPjzPArlHxKLmQV7sUi4H4K4AbNNB8N2s7p3umrLPsv0kqOYlW2A5M/HQhww9akD8yZazZQcKKVRBem3twkbO7sU9OeKKi+XirfMNrf0t3Y7N6vTdb+5P6NxLO7c9BIZf63rUXiriyGvOxzBT/kV1oOcVuU/ik8YEumrjf0V25nr8QXZKbjq6bnzxplOpypxmqV6wUGQkLfrip65GAWGnun/L2ptSeswY9Jmr0AiIyVCBgzKljhSmt2uRtRScA2Yr2C4NSNK2W9+9V9LoTeEAO546IM6x8ZMcUuXdQf3vwcPWm+oZ/j+lY1W+9/VuezyzST0MbtfCkiNGfIt0f9vKnGxi9i15hWkbmjVkCGdtmhrSUTrV2fmA6uaj4C0Iq+lcr0vgWe6MghPxOYSBvEgEIjZLhNGoBAw7czi0SlC3kdwB0e1iIiTyI0pwd53hLMyyet6OVPByVnhz0no0oFsdclo5zpgocvPdJEwJoze7PLDIdlGCQXitZwG2SzBBApQAV0vgMahjrAplPiecWp6uMz5VW8jr4ANcknSkt2AcDYeDQFIDocdnUhf3a2R6m5AecooKMXIcYZWQILXbu4zui75K/XxQhZXQQ61GyQ2aT/AGg1L514xh22C0TheA0Dtw1RmNgoDhCmk7yY58XC7dKY8Afx+Gc2L5GynzSDnMyhZ8QprSBk5XV0Qob/O0j5vbadef3bIwpEp02g8ifKkmoPC05b2VXam9JbtaygMNGfWbpwe+pZxvEBNVvh5/0GzH0U2UXXZ4XAb+JYi9K1c+YnZXs1GvKCAA1zAkq9a8AAyRQGC/fXzJKdI7vWgYRmVLKTfR8nKyAfQRM4gQmpKg8MVdxkOHCwtzNDdxKPZvt9d/TZMj1wfRqHDDYJt6drESA69G4rqCUWUErC8AdWTjc9+FW2WqhMRwlE7hghWiLt25ijI4dvrr0oddiKrtFeWV0EfDTug0nIXz8/PwFrAH8CfwX9Cv4V8iv0V9iv8F8RvyJ/Rf2K/hXzK/ZX3K/4Xwm/En8l/Ur+lfIr9Vfar/RfGb8yf2X9yv6V8yv3V96v/F8Fvwp/Ff0q/lXyq/RX2a/yXxW/Kn9V/ar+VfOr9lfdr/pfDb8afzX9av7V8qv1V9uv9l8dvzp/df3q/tXzq/dX36/+XwO/Bn8N/Rr+NfJr9NfYr/FfE78mf039mv4182v219yv+V8LvxZ/Lf1a/rXya/XX2q/1Xxu/Nn9t/dr+tfNr99fer/1fB78Ofx39Ov518uv019mv818Xvy5/Xf26/nXz6/bXv193v+5/Pfx6/PX06/nXy6/XX2+/3n99/Pr89fXr+9ef9d/49+w5rLyt8w+SE1mXMPDQQUrHqP8sZlFJ3UHKiBI9aaFQeUf3LCeMeYjjHZx9Cy0UYyoAmTB0ltFp/QHfKTR/Z8r4bvprHhYLFuWjb26Ls2El4jnNQdBCaKxUJJG7ezpW6u9kbOCjBRFGXAjTRyz6ERbiAFU2jZff2UesodLNK8wWUrHsQOEjGStmQH28aSIzgw7nVMo1ix6bsp1dpsZydTNngHTujVdwC8oVdBxU0szv4IfZyNWknJPx5SVYXWiydktV/Eztvj4ZhyfZQdwyaVkmZ73MNupcJ5NjPpm6O8lptnI9DyoGyOVLuISBNqZYmRPvIB8qWH+dLiXDIcULRB5lVrME0oK/FclmJiv2jzunxVGCMU8Y63VxT1RTEWAHzS0iEZ9Um2eGl3OPH1wMDlTlD04Xo4+pfJgRM/necwPQmEGxa0Z1fLju++xWCj8l4T6j4x3rHQobbxzCG0Tu20CcQw0oXpk+oreYlI5crXiymX0gJ+42tZaQIyFlyNs=
*/