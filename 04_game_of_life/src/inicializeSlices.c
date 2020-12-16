void inicializeSlices(int nSlicesH, int nSlicesW, int sliceFieldsH, int sliceFieldsW,
       int ((*cellSliceActual)[nSlicesH][nSlicesW])[sliceFieldsH + 2][sliceFieldsW + 2])
{
    for(int hSlices=0; hSlices < nSlicesH; hSlices++)
    {
        for(int wSlices=0; wSlices < nSlicesW; wSlices++)
        {
            for (int y=0; y < sliceFieldsH + 2; y++)
            {
                for(int x=0; x < sliceFieldsW + 2; x++)
                {
                    ((*cellSliceActual)[hSlices][wSlices])[y][x] = -99;
                }
            }
        }
    }
}

