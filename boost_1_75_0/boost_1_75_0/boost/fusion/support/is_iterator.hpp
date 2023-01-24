/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_ITERATOR_05062005_1219)
#define FUSION_IS_ITERATOR_05062005_1219

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_root;

    template <typename T>
    struct is_fusion_iterator : is_base_of<iterator_root, T> {};
}}

#endif

/* is_iterator.hpp
qiVam/ESbZnDxVz9hRId9ZSoU6ihi7FvO2RSj5YKwTF5vvqCXbLQldoo25q939Ps6FpGZrlF7V1PmN32ZhPyGpWV/U5TN6h2dG35QLXPafZ83aNmC8owW/NX3yhHzcQ32Jj+i6dsXm4LZWufs3m5TAgzL2f14eblSd+wFVo6Y/KBp7pLaaaPJgTbix+anT46rTTOzzeO/PxGg8jlfcaBjvPH5W0qbIY3oSDHeVbSp3Suyov1bpvGi83wGmq82AyvisaLtY8iT7VXhuSV/486RbYgFxx3x82mRkM94tIHhrIqUEqiQ28mHZm75fI78omvWe2V+VYt8mebnkbGKMeWpu+4I58cKz23UL6z5fE0h3xPy+05OvPWA9Qy3Pe6rbzXtTpoqtfhQPZrfW7rzF6f1r9DI1gypw+YnL2ycjpZPU8edc7WyONzR0djj1ydfStPnTzT+Z1Qg+Td7VuxG8/L7+43HfUgKVI5bIRyun9KO+1xdXZ1xAgvUza5vu8b2rdYU39YM09eL35MNwWw5fTbPZQR/rcersfmFRueCWvqoQ0GzGjvBhmXn+PulnSjAW6I+5Q0Xwh49P5N7cm/Ip9r6+Rt6wHCN2/RtvUY4VAJeRUnlYaLV9sqqzjHy7FhIo+B+F6/1WwVJ0AoLMqhVZy31pH9NkAY/jYLCxR+Y2GaDfXPdcGG+uqv4atEUid+4e1CWZ3q/yhHvpAtmNzs
*/