公交车调度系统
一、环形轨道，一辆车，车辆可以双向任意行驶。我们规定车辆的原始位置为0（该位置也是车站1的位置），按顺时针方向每个单位位置坐标加1。如果轨道总长为10，则按顺时针方向走，位置9的下一个为位置0。车站编号同理，也是按顺时针方向依次递增。车速固定，每秒一个单位。停车接人或乘客下车时需要停车一秒钟。无论一次停站完成几个服务停留时间统一为1秒钟。各站之间距离相等，车辆经过站点时，根据调度策略，车辆可以停也可以不停。其他位置不允许停车。车辆只能在站点停站时才能改变行驶方向。

二、各站之间距离可配置，站点个数可配置，调度策略可配置。这三个参数保存在配置文件中，程序要通过读配置文件获取。配置文件的名字为dict.dic。
配置文件为文本文件，以#号开头的行是注释。
每行一个参数，格式为：
参数 = 值
的形式。其中参数有三个，即TOTAL_STATION，代表站点总数，为大于1且小于等于10的整数；DISTANCE，代表每站之间的距离，为大于0且小于6的整数；STRATEGY，代表调度策略，只能是FCFS（先来先服务），SSTF（最短寻找时间优先）和 SCAN（顺便服务）之一。
另外：
1、如果某个参数没有出现在配置文件中，则该参数取缺省值。
三个参数的缺省值如下：
TOTAL_STATION = 5
STRATEGY = FCFS
DISTANCE = 2
2、三个参数在文件中的顺序没有规定。
3、显然，TOTAL_STATION与DISTANCE乘积就是轨道总长度，所以配置文件中没有这个参数。
配置文件格式明确：
1、井号只可能出现在每一行的开头；
2、每个参数前无空格，参数名，等号，参数值用空格分隔。

三、输入格式：
若干行，每行一个指令。
指令共5种。分别为end、clock、counterclockwise、clockwise 和target。
其中end是程序退出指令（不是停运指令，是时钟停止，程序退出的意思），只在最后一行出现一次；
clock是时钟指令，每出现一次代表过了一秒钟；
counterclockwise、clockwise、target为请求指令，如果它们出现，同一行内后边一定有一个整数。如果是counterclockwise和clockwise，代表站台上的请求，后边的整数代表请求发生的站点号，counterclockwise表示逆时针方向乘车请求，clockwise代表顺时针方向乘车请求。如果是target，代表车厢内下车请求，后边的整数代表要去的站点号。

四、输出格式：
程序开始，先输出一次初始状态，然后每个clock输出一次当前状态；程序退出时输出end。每次输出的格式如下：
TIME:秒数
BUS:
position:0
target: 0000000000
STATION:
clockwise: 0000000000
counterclockwise: 0000000000

首先输出当前的时间，即已过的秒数。
然后三行代表车辆，BUS:固定不变，position:固定不变，后边的数字代表当前车辆位置，target:固定不变，后边一排数字依次代表车内站点请求情况，0表示没有请求，1表示有请求。
最后三行代表各站点的状态，STATION: 固定不变，clockwise: 固定不变，后边的数字依次代表各站点顺时针方向的请求情况，0表示没有请求，1表示有请求。counterclockwise: 固定不变，后边的数字依次代表各站点逆时针方向的请求情况，0表示没有请求，1表示有请求。
具体可参考输入样例。

五、调度策略补充说明(基于PPT上对策略的说明)：
1、公交车在没有等待完成的请求时，留在当前位置静止不动；只有收到上车请求或下车请求，确定服务目标后，才进入行驶状态。
2、每一个请求，在发出的时候，立即可调度，且调度时间忽略不计，无需等待下一秒信号再批量处理。例如后续的样例中，第1秒信号后发出3号站的逆时针上车请求；则立刻启动调度，小车行驶，第2秒信号发出后输出小车的位置，就已经到达位置1。
3、每一个请求均为单独的服务，就是说车内请求与站台请求没有必然联系。
4、当车完成服务时要选择路程短的方向行驶，如果两个方向路程相同则选择顺时针方向。
5、如果在某个请求没有完成时再有相同的请求（请求类型和站点全部相同才是相同）发生，则该请求被抛弃（不影响策略指标的计算，既不计入等待请求数，又不计入已完成请求数）。如果已完成的请求再次发生时应按新请求处理。
6、对于先来先服务策略，车一次停站只完成一个请求（无须考虑顺、逆的请求方向），即使在这个车站上即有乘车请求，车内也有到该站的请求，也只能按策略完成已经调度的那个请求。但是完成当前请求后，如果发现时间序列上后续的一个或多个连续请求都恰好在同一站点（即连续的同站点请求，位置相同，但请求类型不同），则可以立即完成这些连续的同站点请求。也就是说特殊情况下，一次停车可完成多个请求。
7、对于最短寻找时间优先策略，为了避免长时间不响应较远请求，加入顺便服务，因此需要区分调度的目标站（当前仅1个）和顺便站（公交车驶往目标站的最短路程中，途经站点的下车请求、途经站点的同方向上车请求，可能多个）。先收到的请求只要调度后确定为目标，在完成该目标请求之前不允许更改，即使途中收到更快可完成的请求也不可以更改目标，只能算作顺便服务，允许途经时停靠顺便服务。注意不是所有途径站点的请求都可以算作顺便服务请求，与当前行驶方向相反的途经站上车请求不能顺便服务。即公交车停靠顺便服务站点时，停一次车只能完成下车请求和同方向的上车请求。而公交车到达目标站点停靠时，可以停一次车完成该站点的已接收所有请求，不必考虑上车请求的方向（区别于顺便站停靠）。

8、对于顺便服务策略，第一个目标是全部已发出请求中完成时间最短的那个请求，第一次行驶方向是完成第一个目标的最短路程的方向。完成服务时，无须考虑顺、逆的请求方向。在行驶过程中，如果所有的请求按照当前的行驶方向找出的最短完成时间都超过跑完轨道一半距离时间时，应该切换行驶方向。这是唯一的一个切换方向的规则。公交车在向目标请求站点行驶的过程中，如果收到途经站点的请求（不论方向，但不能违反下一条的提前1秒规则），则不管这个请求的类型一律停靠站点，完成此请求。这意味着一次停车可能完成3个服务。

9、提前1秒规则，对于后两种策略，如果车辆途经某站点时（到达站点位置），刚好收到此站点的上车或下车请求，不能立即服务此请求！要求至少在公交车到达该站点位置之前1秒，发出该站点的请求，才允许途经时完成服务。例如：第N秒信号后，当前公交车到达X站点，但只途经不停靠，在下一秒信号来之前，收到X站点的上车请求或下车请求，该请求只能排在调度队列中，等待下一次停靠X站点才能完成。
【请求至少在公交车到请求位置前一个clock发出，到达该请求位置时再发出请求的不能立即调度服务。】

规则明确：（V8）
车处于停止状态时（可能是停站，也可能是没有请求），如果本站有请求且根据规则可以为该请求服务，则该请求立即完成，不再停1秒钟。



六、输入样例：（配置参数为TOTAL_STATION = 10、STRATEGY = FCFS、DISTANCE = 3）
clock
counterclockwise 3
clock
clock
clock
clock
clock
clock
target 10
clock
clock
clock
clock
clock
clock
clock
clock
clock
clock
clock
end

七、输出样例：（配置参数为TOTAL_STATION = 10、STRATEGY = FCFS、DISTANCE = 3）TIME:0
BUS:
position:0
target: 0000000000
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
TIME:1
BUS:
position:0
target: 0000000000
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
TIME:2
BUS:
position:1
target: 0000000000
STATION:
clockwise: 0000000000
counterclockwise: 0010000000
TIME:3
BUS:
position:2
target: 0000000000
STATION:
clockwise: 0000000000
counterclockwise: 0010000000
TIME:4
BUS:
position:3
target: 0000000000
STATION:
clockwise: 0000000000
counterclockwise: 0010000000
TIME:5
BUS:
position:4
target: 0000000000
STATION:
clockwise: 0000000000
counterclockwise: 0010000000
TIME:6
BUS:
position:5
target: 0000000000
STATION:
clockwise: 0000000000
counterclockwise: 0010000000
TIME:7
BUS:
position:6
target: 0000000000
STATION:
clockwise: 0000000000
counterclockwise: 0010000000
TIME:8
BUS:
position:6
target: 0000000001
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
TIME:9
BUS:
position:5
target: 0000000001
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
TIME:10
BUS:
position:4
target: 0000000001
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
TIME:11
BUS:
position:3
target: 0000000001
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
TIME:12
BUS:
position:2
target: 0000000001
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
TIME:13
BUS:
position:1
target: 0000000001
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
TIME:14
BUS:
position:0
target: 0000000001
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
TIME:15
BUS:
position:29
target: 0000000001
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
TIME:16
BUS:
position:28
target: 0000000001
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
TIME:17
BUS:
position:27
target: 0000000001
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
TIME:18
BUS:
position:27
target: 0000000000
STATION:
clockwise: 0000000000
counterclockwise: 0000000000
end
