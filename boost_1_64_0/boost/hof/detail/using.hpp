/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    using.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_USING_HPP
#define BOOST_HOF_GUARD_USING_HPP

#include <boost/hof/config.hpp>

#if BOOST_HOF_HAS_TEMPLATE_ALIAS
#define BOOST_HOF_USING(name, ...) using name = __VA_ARGS__
#define BOOST_HOF_USING_TYPENAME(name, ...) using name = typename __VA_ARGS__
#else
#define BOOST_HOF_USING(name, ...) struct name : std::enable_if<true, __VA_ARGS__>::type {}
#define BOOST_HOF_USING_TYPENAME(name, ...) struct name : __VA_ARGS__ {}
#endif

#endif

/* using.hpp
MxjnLZbBu4Zi9QyTpB9y+m3pgbFHApCnZiqzlva0c0+3kvPlT6tqNzNE1gkEVOswsFUMe+q8hpbPGndcgWF5WC6hKPzV8cy1Q028cjP1sCnah6WHmdx6PYZEfuTpLl5sgK5wKNMVZ1gdLxROeh2YQ73AdyS9NGv/yC790zGi4LjXmkR5j0JlDDVUB5Z3viRyis3ahgMd/SlM7YIDpbbfBo7d5E/0zzX7v23J2uZ3Q/ZxILCgBdPGopOjZ8zyQo1/2C2zZnwDk0ig6OCwWZ4ZMzGToEwyaO3kA/44SEC6FXV2a/TPNvu/afGXWr0jEcvAjuuCtvz6hBiT55L8aQmxJk9q/u30k5LvTIgzebqDiJ9EEONM3h6B/DwaA1+K8fNDW4JKWHA8EQkjzflDKxInZG2LTFdPMjC5BVeAxJoQr++lWDWOuMDkjqlT/oAZx+SZKctvbozPUYcJ0E0Wz3j6sXvGZm2zxTTj3IS/rIOmn7EdvpYE3EDTmeAdWr0NussU2NdkkcFJRLGKKLhHEWL1pjRJjtfI0Bn4CuQ+5wK0BlYGw+MzkTJxXOEy3VIXJHF/iA+TxGWdqGVZq7IdleBy+ocV0rDzMLyQTdLqe/Ax+WtrCN+/mPCvqwg/NZ/whnnA5ffc/zD/1D7AP7/28E/17fzzyEz++bOCn+X3Vi/HD+Rz/upleKilhxV4aOQckJw3UHC6wumvXsquj7qcoh8yggDIS2PRoykmU0Fj0WN8N0fR36C7CdG1q3ZC8OR+eEaXlCW5YL8f328DC70hBOx0Sqk3aVjY1jSQssJF8VTIKV9iozBvV1hRWFu0ni7BmmHm6sMbEncg8RNFmHETbE8XHWmLq+g6ISphNBm2/nlfDtM/+hdxxiorFeM9Frg+L27johxmod5TWahih3e/b56n+5xXfHXCBOCWjgZl9DUmu6yI0NokYFqUc/Ps77d4B/rm2eO8AwIFyflp8T/r6+mXfxH9JOdfTD9J+aaCB5FpKDlsMpvEt9AQn4rfN5AqkjhnbKysVrcwlHEP9rRPDw5jaQRJg2ZC/Qp/g1pgGI1ZnKswZGxx+mcI2IXCV6sOt2hAHNiZvoqlSQ345Kb7k+h54tSp3FTjjoYXMJr5SdZHRuXH40x2hdIRiXF8ezoqO7ydkn0zjmMU7DRxZlzu5771XsEzuIAG2yyNnqTqrZ4uJ5tXmeDUVl5bdBwtmMk2ijuziohtDqYcWMpFgHrXffxAp7+gKYcXZLoWZRt7JAsHh3BtqDdx7bcRd5u9eofXGtiY1GO0ybSxBStXP+9InNyJEuJ36pTP0ROVYlQ5Dl1Rm2qvIj1WXX6KP2NFEyg2+yxmf7FZfP3P6lss3rQU6pQqhC11PZu3xmF/Ju9phz332Gxc2XktJtIugZdEC/iK4B5cbpp7rPIw6j4sZwhUWIdAhWujA/3p3IEasN+ymkbBRafiSk12radiP433vnIY5zEuYFzIuJjxGMZOxuMZT2A8ifE0xtMZK4xnMr6dsYfxPMbzGVcxXsy4hvE9jJcyXsY4k/FgxhmM0xlvXsq7i4y3M25mvJvxXsYHGLcwPshYMD7CuEPu+zHulHuGHPNpfjbxs5mxhbGVsZ1xMmMH41RZP7yfWci4gHEe4xzG2YwzGQ9mnME4nfH0+7ksyzgPPyPsZMpyxpMYZzLOYZzHuJnxYxzqCOPpjNczrme8mXEHY8G4hfEBxnsZ72acx7iZcQHHPJ5zMo2f1/NzPePx7KeO8aOMpzFOZ9cJ7D+Vnx9m+nimbGbKaqb8jfEExivYdQzjYsaFjLez6z0cqobxYsaZTM9mPwf5+TjTFZkHxhmMB0ufjHNkuRgXMi5mPIaxk/E=
*/