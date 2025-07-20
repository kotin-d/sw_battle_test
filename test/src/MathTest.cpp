#include "gtest/gtest.h"
#include "../../src/Logic/Game.h"
#include "../../src/Logic/Map.h"
#include "../../src/Logic/Strategy/PathLinear.h"


TEST(MapCreator, SwBattle)
{
    using namespace sw::logic;
    Map map;
    EXPECT_EQ(map.height(), static_cast<uint32_t>(0));
    EXPECT_EQ(map.width(), static_cast<uint32_t>(0));

    map.create(15,12);
    EXPECT_EQ(map.height(), static_cast<uint32_t>(12));
    EXPECT_EQ(map.width(), static_cast<uint32_t>(15));
}

TEST(LinearPath, SwBattle)
{
    using namespace sw::logic;
    {
        PathLinear path;
        path.setStartPoint({2,2});
        path.setEndPoint({4,4});

        EXPECT_EQ(path.nextPosition(), Position({3,3}));
        EXPECT_EQ(path.nextPosition(), Position({4,4}));
    }

    {
        PathLinear path;
        path.setStartPoint({2, 1});
        path.setEndPoint({4,5});

        EXPECT_EQ(path.nextPosition(), Position({3,2}));
        EXPECT_EQ(path.nextPosition(), Position({3,3}));
        EXPECT_EQ(path.nextPosition(), Position({4,4}));
        EXPECT_EQ(path.nextPosition(), Position({4,5}));
    }

    {
        PathLinear path;
        path.setStartPoint({1, 2});
        path.setEndPoint({5, 4});
        path.generate();

        EXPECT_EQ(path.nextPosition(), Position({2,3}));
        EXPECT_EQ(path.nextPosition(), Position({3,3}));
        EXPECT_EQ(path.nextPosition(), Position({4,4}));
        EXPECT_EQ(path.nextPosition(), Position({5,4}));
    }
}
