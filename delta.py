import pyarrow as pa
import pandas as pd
pa.get_include()
import pyarrow.parquet as pq
import pyarrow.fs as fs
from deltalake import write_deltalake

# from asammdf import MDF
# mdf=MDF("/Users/ashsubr/Downloads/167-1275_4JGFF5KE5LA054631_3306_20231214_210223.mf4")
# channel_data = mdf.get("ScFuncMon_CurrEst[5].result.value")
# channel_data
# df=mdf.get_group(418,time_as_date=True)
# df['DateTime']=df.index.astype('int64')

#column_data=df[["ASAM.M.SCALAR.FLOAT32.IDENTICAL.DISCRETE"]]
#row = column_data.iloc[5699]
#print(row)
# df

def processtable(table):
    print(table)
    write_deltalake(
    "abc",
    table,
    mode="overwrite",
    engine="rust",)
    
    return "Success"
