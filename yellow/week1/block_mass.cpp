#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    uint blk_nr = 0;
    uint16_t density = 0;
    uint32_t W, H, D;
    uint64_t total_mass = 0;

    cin >> blk_nr >> density;
    for(size_t i = 0; i < blk_nr; i++)
    {
        cin >> W >> H >> D;
        uint64_t mass = W * H * D * density;
        total_mass += mass;
    }

    cout<<total_mass<<endl;

    return 0;
}
