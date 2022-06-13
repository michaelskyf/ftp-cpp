#include <gtest/gtest.h>
#include <stdexcept>

#include "../src/listener.hpp"

/**
 * @brief Test if server accepts both IPv4 and IPv6 addresses
 *
 */
TEST(server, sample_test)
{
	const char *test_addresses[] =
	{
		"127.0.0.1",
		"::FFFF:127.0.0.1",
		"::1",
	};

	const char *invalid[] =
	{
		"1270.0.1,",
		":FFFF:127.0.0.1",
		"::xd:1",
	};

	size_t addr_len = sizeof(test_addresses)/sizeof(*test_addresses);
	size_t inv_len = sizeof(invalid)/sizeof(*invalid);
	SocketListener *sl;

	for(size_t i = 0; i < addr_len; i++)
	{
		sl = nullptr;
		EXPECT_NO_THROW(sl = new SocketListener(test_addresses[i], 8787));
		EXPECT_NE(sl, nullptr);
		delete sl;
	}

	for(size_t i = 0; i < inv_len; i++)
	{
		sl = nullptr;
		EXPECT_THROW(sl = new SocketListener(invalid[i], 8787), std::runtime_error);
		EXPECT_EQ(sl, nullptr);
		if(sl != nullptr)
		{
			delete sl;
		}
	}
}
