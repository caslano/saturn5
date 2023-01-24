/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_CLANG_HPP
#define BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_CLANG_HPP

#if __has_builtin(__builtin_assume_aligned)
#define BOOST_ALIGN_ASSUME_ALIGNED(p, n) \
(p) = static_cast<__typeof__(p)>(__builtin_assume_aligned((p), (n)))
#else
#define BOOST_ALIGN_ASSUME_ALIGNED(p, n)
#endif

#endif

/* assume_aligned_clang.hpp
u52YHFxvtZkO+jaHj7gbdtbVlEAeXgJ+DEbt1XPjiXXYH78TaNmicfQFk49UMs6cFlRKi7+6jI6KhnGaBRD+BLR4DDnCUlFKA6xRLAV4b+0R2Ol0Akyrii7aUooe2obwujLjGhOcGkW8V5Ek+lpkfwLJGGUlnm8g+/iqBxDVl8J741hexFGHvN8ZyWYPPONGcUeSr09Cr/zcSX1lJJJIRO7R3xU8g4voiY2w3YJwD/UpOPuwkW4d5LhS8G/OcioG8nisavCGgsiNCqCSjJrz0cunZ93AZIzf9jZVUv9W8NZwvj3MfKlm1l7eRnJGX30mcr6hTT5ICgnTsLILGF3lGGI/UpJ5uB/V4AlGXG4IoKXe5wrHI+KcOsATr+3lmabflpN6sarRIxdNDGAd06JPNoeWoKkWklC7BkVdkcO6Ju+gtbp6DYIjk1dcaeeWETkl6C7WLxNuyhQzczB4Ao5LzpJhTXSunJ6m7wBlKqSc3rOHZyGBgxJl8flJ9AV+xZ5mVlk2jBAtUK/sSmB+ejQPvJ9VvHxbCwsaXczpDM2sGr7r1FGnldA+XSYi1y0Vph51otoBXFuiQnbPmdU2gWMe1Va+5DYbY5vQZ8jikXddq0gBa53DeM2RxCnYguextzvuGTrcXobmEVa9wzIQrEK2uoMzJbTsnTlN/NNcqgJfuUmNcikoqaJaEGV8WZkHcmFehYX11fguhegdDdAd
*/