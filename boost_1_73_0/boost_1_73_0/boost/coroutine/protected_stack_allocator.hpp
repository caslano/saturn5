
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_WINDOWS)
# include <boost/coroutine/windows/protected_stack_allocator.hpp>
#else
# include <boost/coroutine/posix/protected_stack_allocator.hpp>
#endif

/* protected_stack_allocator.hpp
kL+TsifuGfAKWcHAjcCLBrAikkkbbrz4MpzHcOPOZm4QLyC8ADdYdHhXXnCO2mDoVQC9rwWVyEIA29Qlo9kL5z+00i0nvoTxfOaH0zg5D6LED8eun3jTQ9iHwd4x/NFUWtwHAxiUbKWzD0fO/pGzixP6X0KJfEgkVTrP+EVJSUSNLiFwryfW29DLHfCmt4dAssycFDOxYphI3IWqlby8pXrSwESLIJxGXmT9xKq0bDIKp9pvK8Tis2VcpBznX9MZ6hXYLlAiJSrlTSqoyYII2O6YbP1qfJ5PovHMm8ZeGFgRVqwWQ8lTUra0l7nX7V/mU1wk7Y6OueiL0BxJcVNhFhHrZkMr9X2RGpU91LRjYJSc8koRLHQCklVrrLwXYcI6JpbWWbV2AFpiqL026jqIwdz3u2IzjDKak6ZEn1QpNIJhxqufVU9Mg9U0ZTlL0U/vZcuxLN0SSI3SS4mBzjjmo+Kq7Sto+Y3S2nho2WDP4FhDQHKlj9950+SslpzThfXCnfuxpWmaieksjMNx6EeWqwsdZyZ/utdTf2I5VW616TOS++1ZclnF1BATxfKhntyCfyz4f+71xFPOcbBh0Pcwek+wrqiT8s0o59zBeAwQ8F2UV8oZ5PTT7skJOc7zk5weHJ6sDveOWyCBuXnO
*/