extproc sh

khn_ver=$(sed -n 's/#define KHN_VERSION.*"\(.*\)"/\1/p' khn.h)
khn_short_ver=$(echo $khn_ver|sed 's/[^0-9]//g')

sed -e "s/@SHORT_VER@/$khn_short_ver/g" -e "s/@VER@/$khn_ver/g" khn.txt > khn$khn_short_ver.txt
mv khn.zip khn$khn_short_ver.zip
