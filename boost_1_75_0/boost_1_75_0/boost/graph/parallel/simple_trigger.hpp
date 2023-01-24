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
1esiuffbtqo1Aov60e052rxDf84YqmIw1GXzmK/iqDLdWayz0W7nPv6V/MfPOaYnnQLWwrNmTY20TtAs/WINwYLlXKwH124STb6Z/u1rh9nx25pOBwbxiT6E3ajxzdEVxpY3o2k4y772By1KnTSflzrwikg4X7qskx/ioxgRzP7PBEwzscrLxBIQolrGU6o0sPzMa+cpxjiw/h/T/adoh7yKhaFAbCEVGoLH8NXvwbGPV9VTJVuN3Qrd6t0y0CMBuIFPkklBPTwDLuYODU2CEcANU4UKDrvzJenPbkpxGwiYtqV+MjhZi+sOCt8y2Ri+uZ3FhAstAgme2CoQ1nBu/5AupQCZjeA9olmSqwW/VkTjAH+vwJ9MGLd/I4cuAuJudabX2dkBkfpjQr+zk+xhhUYe84BHYGt2l0bGErknQ0Vzku2UQqpkj3AQPVrjqDfYNxT/8aPtS/FrkKkJ+IK15KCtCwngkGy8tg/gyW5rxpoDEdfW+6XPicRBlfwxvUPmmhNBSv4aCKkyJ3bD1Idk/uG5u0Qs7Q1N8rSHZNfosgu2at4buj2P4t2AuLILPtNvxxnjemkP3LO0nze429YPT33uTLtGlGdjvf1FrVPZ7HvZsncU/UEkG19YCFlLrJ23J7ZWCwbv/X4D/qjeFPLgnne22zcwTqLYsJdo8kIXqxQ3SnAqIyjSEb2CWK+m1nINpXu4YDQccN18m2/n
*/