#include <fstream>
#include <ctime>
#include <vector>
#include "Mod.h"

using namespace std;

int main() {
  clock_t t;
  std::vector<float> times;
  for(int i = 0; i < 10; i++){
  t = clock();
  ifstream in ("in.txt");
  ifstream out ("out.txt");

  long n;
  in >> n;

  Mod::set_modulus(17);
  cout << "testing your conditionals\n";

  bool bad = true;

  if (!(Mod(-12) == Mod(22)))
    cout << "check your ==(Mod, Mod)\n";
  else if (!(Mod(-12) == 22))
    cout << "check your ==(long, Mod)\n";
  else if (Mod(22) != Mod(-12))
    cout << "check your !=(Mod, Mod)\n";
  else if (Mod(5) != -12)
    cout << "check your !=(long, Mod)\n";
  else
    bad = false;

  if (bad)
    return 0;

  cout << "conditionals all good\n";
  cout << "testing arithmetic...\n";

  for (int i = 0; i < n; i++) {
    long prime;
    in >> prime;
    Mod::set_modulus(prime);

    for (int j = 0; j < 180; j++) {
      long a, b;
      in >> a >> b;

      int c;
      in >> c;

      Mod ans(0);

      Mod A(a), B(b);
      int co = 0;
      for (int s = 0; s < 5; s++) {
        if (s == 3 && c & 1) continue;
        if (s == 4 && c > 1) continue;
        co++;
        out >> ans;

        Mod myans(!s ? A + B : !(s - 1) ? A - B : !(s - 2) ? A*B : !(s - 3) ? A / B : A.pwr(b));

        if (myans != ans) {
          cout << "wrong answer for " << a << " " << (!s ? "+" : !(s - 1) ? "-" : !(s - 2) ? "*" : !(s - 3) ? "/" : "pwr") << " " << b << " (mod " << prime << ")\n";
          cout << "correct: " << ans << ", your answer: " << myans << endl;
          bad = true;
          break;
        }
      }
      if (bad) break;
    }
    if (bad) break;
  }
  if (!bad) cout << "all passed!!!\n";

  in.close();
  out.close();
  t = clock() - t;
  times.push_back((float)t);
  }
  float s = 0;
  for (int i = 0; i < 10; ++i)
  {
  	s += times[i];
  }
  
  cout << s/(CLOCKS_PER_SEC * 10) << " s" << endl;
  return 0;
}


//int main() {
//  vector<long> bigp{1361102843, 1012716737, 1413980441, 228358243, 217506911, 775077031, 1464415189, 1557248647, 1092109549, 1467966067, 780771491, 142423717, 424130573, 621692377, 38217913, 1350162731, 983766941, 1619384017, 408180541, 1998453211, 663953393, 44856037, 1241084629, 811378877, 1105279339, 1822612339, 778965281, 2029227359, 123012353, 238562167, 581045947, 1188986483, 286892849, 366211319, 207220511, 819311747, 221148419, 1344834107, 1297195483, 1293756301, 640608599, 704620597, 714304207, 1459947331, 1060350341, 542439323, 515993057, 1078146767, 1672078987, 1269152957, 14593681, 1977600571, 1438604767, 1322070913, 1794247321, 948593819, 266627393, 1649841659, 1937563997, 1303517231, 1475848571, 827308411, 955128023, 130880447, 1953670129, 1559737337, 1794180361, 1096159993, 1227613067, 1086391711, 748580341, 1967697869, 2012534551, 210976313, 650649647, 885692711, 1944070379, 145416889, 1634024731, 1665678437, 708532117, 810433553, 1081877663, 935785847, 306663113, 2027682563, 12354157, 1599707059, 1998471367, 915701819, 921084613, 854277427, 1734612437, 1373429657, 1906466633, 912637679, 497455279, 505635881, 751590457, 1480100467, 2025189121, 1809625309, 820039697, 468915133, 1917228479, 166817503, 919667137, 680080327, 619898831, 996106519, 1144805833, 1398789349, 676088719, 971924587, 1514742821, 1350907697, 1007410687, 116515703, 828092357, 1582678387, 722068309, 294077233, 34262651, 456797381, 478016299, 1016258171, 1793146573, 1756032233, 1445037541, 1418209811, 636822187, 1329878443, 868796507, 1275111941, 987284663, 258345707, 1196801549, 1901938271, 740167733, 978615191, 676583759, 1211799377, 189041023, 1035634381, 1433275229, 1001413331, 1694081551, 1729237309, 558550621, 404178683, 249372317, 1884646241, 1665255521, 960530537, 441494597, 621792037, 1048865837, 88400393, 131674393, 1270013093, 2011804133, 1997963119, 1604897321, 993101321, 1532737117, 767649787, 658189991, 1748706067, 479723767, 171435419, 525633943, 686431433, 379538521, 2002769641, 726158581, 1254783443, 1000697371, 887445059, 331553603, 1125974767, 82409869, 1743746689, 645259547, 836749603, 422954159, 39830467, 1795518467, 119628557, 186821147, 549573847, 1396131199, 1537785859, 952622953, 92931221, 1362224719, 1471655149, 1895412877, 69699967, 465486191, 1073565491, 1377986801, 284343889, 916910903, 162652337, 1126845719, 852995851, 683063681, 1725624073, 106418321, 947885657, 155040667, 232130149, 1022677237, 396765799, 517292263, 1759202491, 1781900401, 1916847269, 1509729271, 750954661, 1846411337, 1180410383, 498582697, 1732386787, 1230787603, 172415189, 2009042531, 248497603, 1120273127, 1832972467, 1761603713, 602193157, 243698789, 830091187, 1056184903, 1572655949, 1367658841, 1222821371, 1260142817, 1144471931, 1315046729, 1626063661, 206659267, 1176930877, 1467597499, 1602647317, 1972961219, 644065691, 1630239613, 1378643843, 1565686987, 1186677101, 448482851, 630718607, 644206397, 1857351961, 497617031, 2034495787, 847540741, 375906691, 1101422887, 1505898467, 456141793, 2024892629, 670089053, 505115837, 1934496227, 352554023, 1271562647, 138528541, 317386793, 1626079799, 1365339187, 1255553333, 816046171, 343325053, 1626819503, 1663063291, 994026157, 243753121, 333863591, 1240339739, 360656249, 1107616183, 1920700541, 568945789, 1577779849, 1165934303, 466488131, 556221989, 2004840437, 444184157, 1191261353, 618215497, 259662253, 272174519, 159384529, 52739363, 1474080847, 1726444199, 420802489, 1086706163, 1421223703, 1552499183, 197655839, 248722361, 944513891, 1216536407, 871262489, 142024367, 598612111, 59999, 965016839, 1699443491, 1809442541, 450221971, 1003362149, 1009130593, 1523664503, 1011764959, 115738963, 223804073, 1743249587, 1648603739, 1862900687, 979988063, 965843909, 701985959, 119642521, 1906830137, 912004013, 1477653253, 330838939, 1746310543, 548455129, 106236821, 712550453, 457010909, 1932078149, 1832027051, 320397281, 919095523, 2032385969, 1974909847, 918757523, 936580633, 963453977, 1915255093, 252983131, 1279847497, 1781488367, 416466961, 501761563, 204365101, 189241457, 1134837331, 1480280371, 253461751, 1749472037, 1691022559, 416872471, 150337751, 1395756917, 643322191, 779477509, 434630267, 1015456027, 1608740597, 1303683701, 1768278949, 1303538459, 1130905483, 532556357, 1781348267, 206677507, 270511279, 159860081, 1300922543, 1202177707, 860952347, 531813367, 1569791813, 797053769, 1686817421, 1462279477, 1265243249, 1584979523, 1854480059, 1251411349, 1547656961, 57069599, 1449945907, 1849781933, 2005117199, 1374599021, 25566797, 126425953, 1752277169, 61858061, 78137393, 1881053467, 156563569, 856290557, 272879023, 1093522571, 1606287223, 552823211, 419629807, 746960191, 1087164431, 650317583, 107206849, 1465858421, 519973507, 427059167, 918077437, 1112481883, 1512338141, 563663213, 1953074623, 1757198977, 1131161957, 682099819, 1057965079, 1138266709, 761727779, 33497297, 1128575999, 699625229, 1432902791, 1394452067, 480325003, 587413447, 1418939707, 1910365333, 1091033341, 941578993, 277337807, 1299447473, 305252929, 370217231, 194795339, 1332851747, 1936739069, 78432371, 287958379, 1073237783, 1253378449, 1558774571, 787240049, 296522351, 510379819, 941974973, 531671773, 1481774303, 1519143653, 1129133287, 2006482991, 1974065077, 504954347, 1377914053, 840449243, 701232403, 1681510541, 302253337, 86815361, 835855799, 1507039991, 357521117, 1529049617, 1682175343, 511066667, 1275338917, 793319057, 284557151, 15397693, 1750084321, 1533928393, 630609691, 137882039, 1253417899, 574537199, 882587557, 192124657, 1421226997, 1557364021, 1706127077, 105315409, 303044999, 725007977, 1804626259, 1861351, 1820474917, 1646882221, 650960347, 2008335143, 1159450829, 262672493, 314337841, 570300881, 1890922519, 34676563, 1147439543, 1233195851, 1310839597, 1825498141, 1542007787, 1481854889, 514543937, 824362853, 51100769, 1134276599, 1069274197, 1380955717, 518583983, 43323773, 1193265481, 1932418177, 789801619, 528323813, 5893733, 350222417, 170454749, 1084469779, 1569585133, 1399480997, 807170173, 521075587, 988560073, 555013957, 1970943817, 1104670067, 376243171, 1432834219, 1949344003, 322293001, 1529057891, 1823033561, 509616733, 432547967, 1013572333, 1019758249, 1850829433, 596294911, 1919874109, 1741547497, 139325933, 1700271691, 65507347, 1457289703, 1956414191, 1996351937, 812312021, 259783127, 1726227749, 534278881, 92022509, 2037252983, 1368687389, 1790560049, 1078430033, 1480467311, 560887813, 720169421, 1650758953, 744429583, 521873549, 151754909, 565076051, 970951327, 304037813, 262741483, 1912198283, 1653632839, 1355089891, 1168915243, 1847926679, 203777683,
//                    1384181681, 1697053613, 1980868381, 1662450991, 48493139, 207738023, 676657777, 216531233, 1773412559, 1861414483, 1996687619, 1938115579, 1189466809, 71389397, 1612937003, 1602954979, 97911169, 1009260541, 1423673963, 214123363, 1513660831, 611601337, 1056991069, 425978963, 1578917981, 1831604917, 1803139307, 1528223341, 367394329, 1347026963, 412698323, 1423504507, 722783489, 480845137, 1884821219, 916384577, 1519923761, 384777049, 887396267, 802248043, 18044779, 9282019, 1018119523, 158641157, 1322575399, 244116497, 184421099, 1519595537, 1710004001, 854139079, 1423850431, 1399243399, 340249783, 1779801827, 683942723, 1592483869, 1467693823, 1513014649, 1987562587, 1414689797, 1568180071, 877233001, 1029999679, 195661559, 1506558197, 139754191, 1835079949, 1254971191, 1948318111, 1660547881, 1091676583, 1038023369, 739490237, 1401224623, 411267341, 1729458893, 998646641, 1451125441, 1024358593, 553881763, 319634417, 924557311, 424915237, 298630883, 1730833589, 779436641, 168456173, 661831367, 1304588933, 1638654403, 1206171581, 478011739, 1932572281, 289972391, 440212081, 327509971, 198850699, 434035703, 267989573, 273028031, 1376276623, 953105093, 555177521, 810923, 127875901, 1454796509, 1964255393, 1716213497, 1507754569, 542055167, 1013931857, 615930883, 774255539, 752375599, 547443443, 1011176603, 537307819, 1524512921, 1373768119, 404885309, 1287552367, 636419627, 29727473, 509701271, 794886019, 82659761, 1685215901, 206614453, 1923811859, 319497679, 850796131, 1725889637, 989400101, 1044809729, 471128491, 1664897119, 94038071, 1929946789, 2009363353, 1164134183, 1867118237, 1863168599, 688680247, 1081373857, 746287967, 1267581071, 1819252817, 164915693, 202247471, 1158341651, 142702291, 548646613, 339837767, 616468651, 1489344167, 1111875889, 673352591, 954567671, 1238805133, 1358581729, 1013151409, 561738523, 1039889173, 715678441, 834777851, 1553145943, 1715845441, 568912937, 1651598017, 359054483, 1392071969, 1377017273, 1903764851, 1998480041, 1393375943, 646513837, 1819435087, 1087688087, 848239913, 580378171, 905402237, 1232085697, 442718033, 1530929467, 370215709, 753656279, 127877507, 535743977, 1947245341, 82323419, 1808818237, 846631579, 1519385537, 391973887, 698619067, 1483818253, 1713015151, 43759273, 170820421, 783778729, 1428419471, 121626803, 562573279, 676750973, 743290183, 22721147, 1653660961, 1798841269, 928587949, 341801333, 1746785141, 596391833, 76534369, 744261883, 657545897, 1643979643, 957355621, 150308447, 1930226351, 1351131731, 1971937999, 605864323, 462807503, 1591653829, 497961421, 1457201467, 1022653613, 1181230469, 1121117951, 1760536091, 1602586079, 493479401, 1513750943, 1045653649, 300533137, 1789701239, 1647348709, 729923153, 741494269, 269827997, 423061063, 1341281941, 226475251, 1388646059, 532533223, 33727307, 1523482921, 1035052609, 55922677, 1595741131, 1387379603, 939401423, 1496823001, 139420091, 701154101, 817827961, 30096359, 224650297, 723613523, 414564679, 1651438559, 1280500157, 1430338831, 1963686887, 337487663, 1825860863, 504794761, 1749369053, 1323838121, 245071517, 965174443, 139123241, 1094482919, 1275408499, 1113871337, 962047633, 749518283, 168560291, 1499792291, 1713428081, 1271570903, 875946271, 721507987, 1315058483, 179097161, 131277371, 259126853, 1995305947, 1770663617, 304845491, 1082763917, 269904949, 1772945093, 446204261, 777103399, 1357379641, 1205209507, 1784117117, 1513335451, 908331929, 1307333899, 596857451, 730642387, 1890413023, 1531670747, 580652311, 412578193, 1477606891, 528896051, 648534583, 874688359, 827282431, 887444119, 859906759, 420332959, 158174321, 815681857, 386271757, 1749010343, 1613234353, 1157678329, 244921819, 95607041, 1254169337, 995734513, 1778357059, 582332741, 1323094939, 1377479479, 1250831233, 1924844629, 1152015157, 1364761841, 495222059, 458251909, 312249233, 1773131993, 2031385309, 347567951, 57399547, 1374814577, 1089405311, 814789907, 1073305949, 543478129, 2021473981, 204068983, 1721253019, 1195423373, 999187729, 1363152913, 1122171653, 873059017, 462166379, 627431009, 1629936307, 1094397527, 888387197, 732240083, 704109487, 55243039, 495632021, 493201091, 1138981099, 1281296567, 792273271, 1411634657, 1344794147, 1385636027, 413085139, 1282399903, 226697539, 211421563, 1955246743, 1618563883, 1015632941, 390565607, 1515015329, 1028296547, 1234049629, 1560829741, 1739892311, 757091999, 804793343, 259382663, 1451946403, 1390730491, 279275639, 465248939, 1077208361, 1242156109, 1764728323, 145635629, 15039641, 1360702279, 1009369343, 73033271, 1097080559, 788808281, 1027378277, 1493084501, 93457907, 184857317, 1666219363, 119161193, 519053159, 290039791, 1962920213, 369440909, 103429153, 1514128481, 835270357, 1898573221, 345558217, 960314911, 1135670009, 637877479, 1063341563, 987682673, 1637052199, 1461055691, 59365967};
//  vector<long> smallp{379, 241, 379, 443, 2, 331, 179, 503, 41, 541, 431, 373, 509, 101, 19, 67, 449, 113, 61, 157, 449, 367, 179, 353, 421, 313, 479, 19, 409, 401, 23, 83, 359, 509, 223, 499, 197, 311, 173, 503, 113, 397, 101, 487, 193, 107, 41, 163, 167, 181, 367, 227, 2, 211, 439, 449, 509, 367, 83, 151, 13, 167, 83, 131, 139, 41, 509, 389, 47, 457, 67, 337, 191, 487, 71, 61, 211, 197, 113, 311, 313, 317, 101, 241, 43, 47, 233, 83, 127, 277, 67, 223, 409, 503, 439, 461, 367, 233, 31, 509, 73, 263, 449, 53, 281, 191, 257, 199, 199, 379, 167, 149, 47, 421, 37, 503, 5, 359, 503, 503, 59, 433, 61, 383, 5, 197, 269, 263, 479, 19, 173, 197, 31, 397, 317, 479, 167, 457, 43, 409, 127, 197, 29, 107, 491, 269, 13, 13, 521, 283, 61, 109, 107, 269, 73, 233, 449, 431, 263, 139, 337, 541, 191, 467, 359, 29, 431, 257, 487, 179, 59, 307, 71, 233, 11, 347, 523, 149, 487, 199, 193, 449, 7, 179, 479, 239, 139, 397, 83, 97, 251, 277, 131, 73, 271, 53, 191, 461, 311, 41, 173, 509, 107, 353, 5, 59, 353, 367, 541, 89, 71, 193, 41, 173, 307, 397, 443, 509, 29, 89, 103, 353, 41, 163, 467, 137, 59, 347, 409, 521, 271, 197, 293, 241, 457, 389, 433, 3, 5, 263, 199, 499, 263, 331, 71, 41, 97, 181, 191, 277, 17, 223, 439, 11, 479, 7, 367, 523, 239, 71, 47, 41, 461, 61, 109, 479, 443, 53, 479, 113, 419, 419, 421, 233, 149, 71, 157, 2, 181, 397, 233, 17, 263, 257, 103, 523, 223, 397, 431, 71, 373, 317, 523, 199, 83, 239, 397, 199, 479, 241, 167, 443, 379, 17, 239, 439, 457, 521, 431, 19, 461, 73, 439, 17, 509, 181, 7, 293, 491, 197, 179, 487, 103, 263, 5, 61, 337, 101, 521, 103, 499, 229, 19, 149, 101, 347, 149, 239, 229, 53, 149, 173, 103, 337, 167, 181, 541, 227, 59, 101, 193, 499, 479, 401, 167, 487, 181, 337, 401, 163, 313, 139, 431, 131, 19, 499, 11, 449, 149, 11, 19, 107, 379, 107, 421, 541, 3, 2, 367, 313, 401, 71, 269, 509, 503, 223, 367, 37, 79, 467, 223, 479, 71, 433, 383, 331, 137, 457, 41, 223, 431, 457, 37, 191, 241, 173, 37, 59, 479, 467, 229, 103, 283, 131, 353, 109, 223, 109, 491, 373, 7, 463, 151, 103, 223, 127, 83, 151, 283, 433, 179, 5, 281, 107, 173, 59, 53, 449, 47, 431, 2, 461, 359, 379, 89, 23, 79, 521, 449, 433, 271, 419, 193, 73, 191, 157, 11, 401, 73, 313, 139, 239, 449, 397, 7, 293, 163, 2, 173, 233, 29, 541, 431, 251, 463, 79, 191, 367, 311, 191, 79, 269, 11, 241, 2, 541, 397, 421, 157, 457, 257, 167, 127, 37, 379, 461, 131, 311, 503, 487, 487, 61, 397, 307, 509, 349, 421, 2, 449, 461, 59, 541, 379, 509, 211, 73, 67, 139, 53, 67, 2, 421, 541, 467, 239, 223, 127, 41, 43, 349, 269, 463, 241, 11, 373, 379, 149, 61, 523, 37, 19, 191, 113, 59, 337, 337, 347, 193, 11, 239, 41, 227, 523, 499, 11, 181, 359, 229, 379, 317, 281, 173, 263, 59, 251, 491, 157, 419, 457, 241, 13, 113, 197, 163, 251, 43, 443, 181, 19, 461, 389, 227, 17, 137, 457, 359, 479, 317, 491, 41, 457, 7, 461, 443, 433, 79, 487, 31, 5, 281, 113, 113, 7, 353, 353, 239, 389, 241, 73, 269, 89, 43, 389, 509, 13, 173, 269, 61, 379, 523, 331, 241, 37, 241, 193, 443, 29, 449, 337, 97, 281, 11, 223, 349, 439, 449, 439, 463, 337, 463, 2, 373, 101, 523, 359, 197, 313, 281, 491, 401, 61, 37, 313, 19, 29, 191, 419, 293, 211, 491, 29, 347, 419, 149, 131, 463, 431, 337, 89, 47, 211, 433, 127, 151, 137, 503, 101, 479, 283, 41, 109, 347, 163, 167, 311, 419, 89, 293, 19, 151, 193, 353, 401, 13, 181, 53, 479, 173, 397, 317, 379, 409, 191, 191, 277, 29, 53, 251, 257, 113, 53, 127, 463, 397, 83, 37, 277, 541, 37, 5, 419, 479, 283, 383, 509, 5, 487, 229, 227, 277, 239, 23, 401, 277, 307, 41, 241, 419, 131, 157, 523, 151, 83, 389, 401, 5, 433, 113, 11, 271, 277, 47, 229, 41, 347, 409, 179, 401, 131, 29, 151, 223, 439, 257, 131, 389, 43, 109, 313, 89, 313, 223, 263, 523, 43, 23, 173, 61, 89, 2, 179, 17, 383, 431, 449, 11, 11, 229, 191, 3, 61, 439, 401, 367, 509, 367, 163, 127, 43, 443, 109, 331, 467, 199, 113, 47, 5, 67, 373, 103, 149, 337, 331, 431, 233, 101, 7, 53, 17, 59, 89, 131, 521, 457, 293, 227, 193, 373, 83, 5, 103, 47, 283, 233, 379, 37, 499, 17, 269, 199, 149, 337, 317, 3, 269, 521, 281, 311, 197, 173, 433, 193, 107, 3, 29, 541, 359, 389, 541, 139, 127, 409, 389, 293, 251, 227, 283, 353, 59, 211, 113, 127, 331, 293, 337, 487, 251, 107, 17, 241, 59, 503, 97, 73, 37, 509, 107, 281, 149, 11, 383, 461, 347, 421, 347, 37, 467, 127, 19, 199, 419, 227, 151, 379, 71, 239, 31, 67, 149, 337, 251, 73, 379, 503, 523, 467, 349, 349, 113, 257, 541, 313, 293, 239, 397, 449, 107, 271, 311, 227, 59, 31, 73, 457, 2, 401, 347, 43, 397, 443, 487, 83, 457, 337, 479, 19, 199, 337, 479, 163, 191, 307, 193, 373, 389, 487, 373, 521, 311, 157, 67, 503, 47, 149, 257, 461, 179, 359, 331, 167, 271, 7, 193, 2, 11, 251, 113, 421, 19, 457, 349, 503, 263, 5, 499, 197, 193, 139, 137, 439, 281, 31, 73, 113, 503, 113, 7, 43, 499, 71};
//
//  ofstream in ("in.txt");
//  ofstream out ("out.txt");
//
//  in << (1000 + 1000) << endl;
//
//  srand (time(NULL));
//  for (int i = 0; i < smallp.size() + bigp.size(); i++) {
//    if (i < smallp.size()) {
//      in << smallp[i] << endl;
//      Mod::set_modulus(smallp[i]);
//    } else {
//      in << bigp[i - smallp.size()] << endl;
//      Mod::set_modulus(bigp[i - smallp.size()]);
//    }
//    for (int j = 0; j < 20; j++) {
//      vector<long> nums{rand(), -rand(), 0};
//      for (int k = 0; k < nums.size(); k++) {
//
//        for (int l = 0; l < nums.size(); l++) {
//          in << nums[k] << " "  << nums[l] << " ";
//
//          int code;
//          if (nums[l] >= 0 && Mod(nums[l]) != 0) code = 0;
//          else if (nums[l] >= 0) code = 1;
//          else if (Mod(nums[l]) != 0) code = 2;
//          else code = 3;
//          in << code << "\n" ;
//
//          out << Mod(nums[k]) + Mod(nums[l]) << " ";
//          out << Mod(nums[k]) - Mod(nums[l]) << " ";
//          out << Mod(nums[k]) * Mod(nums[l]) << " ";
//          if (code%2==0) out << Mod(nums[k]) / Mod(nums[l]) << " ";
//          if (code<2) out << Mod(nums[k]).pwr(nums[l]) << " ";
//          out << "\n";
//        }
//      }
//    }
//  }
//
//
//  in.close();
//  out.close();
//  return 0;
//}
