optionLine = {
    tooltip: {
        trigger: 'axis',
        axisPointer:{
            lineStyle:{
                color: '#75c3fb'
            }
        }
        
    },
    grid: {
        top: 70,
        bottom: 50
    },
    xAxis: [
        {
            type: 'category',
            axisTick: {
                alignWithLabel: true
            },
            axisLine: {
                onZero: false,
                lineStyle: {
                    color:'#ccc',
                }
            },
            boundaryGap: false,
            data: times.map(function (str) {
                return str.replace('/', '\n')
            })
        }
    ],
    yAxis: [
        {
            type: 'value',
            axisLine: {
                onZero: false,
                lineStyle: {
                    color:'#ccc',
                }
            },
        }
    ],
    series: [
        {
            name:'使用流量',
            type:'line',
            animation: true,
            smooth: true,
            data: [154,245,567,332,146,134,123],
            itemStyle: {
                normal: {
                    color: '#1fa1e9'
                }
            },
            markPoint: {
                symbol:'pin',
                data: [
                  {xAxis: 0, yAxis: 154},
                  {xAxis: 1, yAxis: 245},
                  {xAxis: 2, yAxis: 567},
                  {xAxis: 3, yAxis: 332},
                  {xAxis: 4, yAxis: 146},
                  {xAxis: 5, yAxis: 134},
                  {xAxis: 6, yAxis: 123}
                ]
            },
            areaStyle: {
                normal: {
                    color: new echarts.graphic.LinearGradient(0, 0, 0, 1, [{
                        offset: 0,
                        color: '#1fa1e9'
                    }, {
                        offset: 1,
                        color: '#ffe'
                    }])
                }
            }
        }
    ]
};

//myChartLine.setOption(optionLine);
