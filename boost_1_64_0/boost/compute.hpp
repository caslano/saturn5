//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_HPP
#define BOOST_COMPUTE_HPP

#include <boost/compute/algorithm.hpp>
#include <boost/compute/allocator.hpp>
#include <boost/compute/async.hpp>
#include <boost/compute/buffer.hpp>
#include <boost/compute/cl.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/config.hpp>
#include <boost/compute/container.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/device.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/image.hpp>
#include <boost/compute/iterator.hpp>
#include <boost/compute/kernel.hpp>
#include <boost/compute/lambda.hpp>
#include <boost/compute/pipe.hpp>
#include <boost/compute/platform.hpp>
#include <boost/compute/program.hpp>
#include <boost/compute/random.hpp>
#include <boost/compute/svm.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/types.hpp>
#include <boost/compute/user_event.hpp>
#include <boost/compute/utility.hpp>
#include <boost/compute/version.hpp>

#ifdef BOOST_COMPUTE_HAVE_HDR_CL_EXT
#include <boost/compute/cl_ext.hpp>
#endif

#endif // BOOST_COMPUTE_HPP

/* compute.hpp
qEm2maYNQQsDlCK3gtQz/peQ7Bj1pRCANnL+DcASwKg9L8soKh8MU//vtrBgPxHcL3YmKKGJYhIO8IUnO7M+U0KXJzthxa7vw14TXThMzqnCLVSIRSCHd9fWL0eJ2Ium5Zp57Wcbv4WJNIg5rKDyTlinqmiKhBCKmF4i5hZDfXoQncGcOcVGYorlYYrFTq/rqqNlGCLL8P5mswxn1HHTuYp2MGEGWCTMS4BhkvH4lLC/1E5HeetGIkFr4IUG8KgocKW29wWjuYm9rvsPIq39+3+G/FNr7r/yCtNrfEdpaq1b6rJYjgG/qhX8mSb8rNbweaMl5bhfpqC0TDuUsIxw6bjOWzjEEWrsOX0M0FyFbnC7Xk1y0gwSyHerNi6Qk7gXKKsCZo+6JLH+SCcyQxxNA/KDfxWWzxSvXEXsKgBQnJHX0KTJlxPXEEl700c1orS0zLQRu5CcWPHctMtBDoSiQtZ6VzJA69sc16Ik+CGDH7xHYlXELmXiHkXheibIxdl/MrlCwwqJQI49r5SWmw8UKbrfZOM+pUhLOMY1Q7KMKJ1bXYcC3oMCgjhow1hGAp2k8P1d7GFjvYWjHCBabjgJQ6yJXKaHDp7umt9WkLaBkTtY6rWu5Q/018Z0tRQdgvXiC7LwZOE+xotor+ItgoMUdiG3a/kW+Na7Xe43BXMtDiEh+MLfIfYlC1jKyKwk5VULOBr4k3pcL9YqRYccwR/Bxx+iS0lECOxeK9/nyncbhCl7fRLAbMG2AINpDTLGTXgrgiX6J3B0RIjb9WLx5Zuu7GqZ6ClZHeyNoTpUiQzXczYHLp3oLqkOZOPvukDiRE9i7UTF9fuDU8+CSW4tnOtztroW3E6itArdw85ATdj4yX4VJacepP7jrIqT64UT/4n1e8zYZpZ7itB/rIruf+vWbJn0qw/Q74xtttsPNnA73+E2Wfj3rAa/vU5Yn8krbhKEupKGTDF1sd3fz/nnx5vXj+CRvpz1ruL7rBQP10Vmp4V2J0Qm5yE2exE0Y8EkpeE1ayAeLarzZAgd6/Wt8JMMjOefS0IHwR2PQtqoB0RmrAdEZqwHBD/s8o1+EPXjRBqnmSYaY6u/VHpj8Lu+v59Uh4vQ3t+KdbCU3J0qNs2zGiqroaIabnTTAOE44ct5N9hWFNuBYh9RGqqd0rDp5hkLpEoTIlfFax5q0Av3Qg1xGcTVT5W2X/g5JWP3jyKHkQVqDWTx3Akwxr0pcpMy3ASYM0G2xtn3Qp/hy2maueUV6olXUseGAgTcrYqHl2ziGyfKqaI76qD+1JHzG+yFNKXtNi1J4nTY99a/TH8Om7o6aoraASmDnE2FNIJPifKvP+wR49/r1+q+cfP8iypDsm6kF0kdOMrNZL0iKY+vo71jh/6WsXm+jpoLV/lHbaZ2d6tQdW/zQz9Cvv412U7v6BX1c9R8h9A4Z21htzDHDO3jV8mubAfKK4CSrFhZAm0myfNNA3XgsRhWjcm1Z5EGhNfPmb+NmfzERmGkHdIBT1uBZz1Idwll952uUvrIRvKtpihu7K46tTvtmvfbdKg0aYAlpXm/DVlvMkOQvd3qmrkHhUfMGeDR+q6F7JQolfFojzzIjaxvxkttKWtNUwBqMUCTW4KmREHjCep1l1KbD9J6O4htVbrDtby2vgvdyf2RlILaFAsCFdeLSZdN7F3bUHl9YEpDpTNwMR3RHcpqi5WYxP4Oi1gFN+jbQms4h9078Glu2NHXN0U37BCW7f3LNSnRJFSHcjZsYAARitCXbCzfsjJ6YE8sqQ2c7RGFihu5pkV9PEvN+tgplAfRa6jNeFfJ9XhrqHK5isfhhciY7WlIXDfqX8Yttp4fpPnS8+dHK6U=
*/