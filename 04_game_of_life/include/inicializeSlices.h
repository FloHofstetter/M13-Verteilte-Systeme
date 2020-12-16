#pragma once

void inicializeSlices(int nSlicesH, int nSlicesW, int sliceFieldsH, int sliceFieldsW,
                      int ((*cellSliceActual)[nSlicesH][nSlicesW])[sliceFieldsH + 2][sliceFieldsW + 2]);
