#pragma once

int fieldSlice(
        int hTotal, int wTotal, int hStart, int wStart, int slices, int(*fullField)[hTotal][wTotal],
        int(*fieldSlice)[hTotal/slices + 3][wTotal/slices + 3]
);
