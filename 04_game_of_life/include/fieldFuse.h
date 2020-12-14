#pragma once

int fieldFuse(
        int hTotal, int wTotal, int hStart, int wStart, int slices, int(*fullField)[hTotal][wTotal],
        int(*fieldSlice)[hTotal/slices + 2][wTotal/slices + 2]
);
