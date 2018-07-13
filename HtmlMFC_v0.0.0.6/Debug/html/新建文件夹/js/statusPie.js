var colors = ['#9231a5', '#51b9a3', '#fc8322','#5e8dd0','#fb52a3'];
optionPie = {
    color: colors,
     grid: {
        left: 10,
        top: 60
    },
    legend: {
        orient: 'vertical',
        x: 'right',
        y: 'center',
        data:['Others','iTunes','Netflix','Dropbox','Chrome']
    },
    series: [
        {
            name:'访问来源',
            type:'pie',
            radius: ['50%', '70%'],
            avoidLabelOverlap: false,
            label: {
                normal: {
                    show: false,
                    position: 'center'
                },
                emphasis: {
                    show: true,
                    textStyle: {
                        fontSize: '20',
                        fontWeight: 'bold'
                    }
                }
            },
            labelLine: {
                normal: {
                    show: false
                }
            },
            data:[
                {value:135, name:'Others'},
                {value:210, name:'iTunes'},
                {value:334, name:'Netflix'},
                {value:535, name:'Dropbox'},
                {value:1548, name:'Chrome'}
            ]
        }
    ]
};
//myChartPie.setOption(optionPie);