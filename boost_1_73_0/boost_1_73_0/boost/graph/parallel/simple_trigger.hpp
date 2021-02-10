// Copyright (C) 2007 Douglas Gregor 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file contains a simplification of the "trigger" method for
// process groups. The simple trigger handles the common case where
// the handler associated with a trigger is a member function bound to
// a particular pointer.

// File moved
#include <boost/property_map/parallel/simple_trigger.hpp>

/* simple_trigger.hpp
qb01nxlPntQe9EGtArULq/CjFR22CtbPy0KKuiim0Ze6MN7UgagjY8SUDPHW56th1LExsuxIgYRfo9ic5wSKccr3mlYCuj+KsVKWvSMPDUTtXwYFImqmcb0qQF4r0P2BaXB1zgZX/dO8qrV3uex2h85Zu3fePeXjOVgFxmBFuAJ3x+jBZ7mdMeTU76gtzecgS/iInYx7hIfL0MNtVnydARur3bXyw+a+fliY92iCAFQcS5vr7UPRWjE3VVuVgN1RUJRhozyrSrmkq7ZtnHs0II1LBKC2F/Q4EXz3XXU2smt/hq5z81FT9ue3gF3rJxXVWEnByt8ZpQ0rT7HH/ie6cqXY4aCFQGC1jDzNP6X+Vkakfd6yPeRrzm1ULyNZcoesLOdDtaCVllJCAFQZhZPUcRvyqA6GRn90w8AjodrkK5jgwZIWB1lY3yZCmyC1mAg+9CxViSp3INsVM6DScu7Dtgp4yw/9OawjKapXKmwMP3Hy1IPG8bInNMx5fhS4IaEAUzWY4NVPGeiKKeVV1dG4y8WCInLmRgcTf+YmnlxeLILgRp8iJ0jS4OjLnxQmnFHzMdA0CTyNF8CYkylt9UE+RgHvJdA7+RqXu6xA69KRsTBZW5ANzzwYYkzxQp2xdvXZn3ukrKsCZOGem17s
*/