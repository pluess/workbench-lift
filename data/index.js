function updateAllSlider() {
    var sliderValue = $("#allpwm").val();
    $("#text_allpwm").html(sliderValue);
    console.log(`updateAllSlider: sliderValue=${sliderValue}`);
    for (var i = 1; i <= 4; i++) {
        $("#motor" + i).val(sliderValue).trigger("change");
    }
}

function updateSliderPWM(element) {
    var sliderValue = $(this).val();
    $("#text_" + $(this).prop("id")).html(sliderValue);
    var motor = parseInt($(this).prop("id").substring(5, 6));
    console.log(`updateSliderPWM: motor=${motor}, sliderValue=${sliderValue}`);
    $.ajax(
        {
            url: "/setpwm",
            data: {
                motor: motor,
                pwm: sliderValue,
            },
            type: "GET"
        }
    )
}

function resetFunction() {
    $("#allpwm").val(700).trigger("change");
    $("#offAll").prop("checked", true).change();
}

function switchAllMotor() {
    var mode = $(this).prop("id");
    mode = mode.substring(0, mode.indexOf("All"));
    for (var i = 1; i <= 4; i++) {
        $("#" + mode + i).prop("checked", true).change();
    }
}

function unsetAllMotor() {
    $('input[type=radio][name=motorAll]').prop("checked", false);
}

function switchMotor(event) {
    var direction = $(this).val();
    var radioName = $(this).attr("name");
    var motor = radioName.substring(5, 6);
    console.log(`switchMotor: direction=${direction}, motor=${motor}`);
    unsetAllMotor();
    $.ajax(
        {
            url: "/motor",
            data: {
                motor: motor,
                direction: direction
            },
            type: "GET"
        }
    )
}

function initPwm(data) {
    console.log(`initPwm: data=${JSON.stringify(data)}`);
    $("#motor1").val(data.motor0);
    $("#motor2").val(data.motor1);
    $("#motor3").val(data.motor2);
    $("#motor4").val(data.motor3);
    $("#text_motor1").html(data.motor0);
    $("#text_motor2").html(data.motor1);
    $("#text_motor3").html(data.motor2);
    $("#text_motor4").html(data.motor3);

    if (data.motor0 == data.motor1 && data.motor0 == data.motor2 && data.motor0 == data.motor3) {
        $("#allpwm").val(data.motor0);
        $("#text_allpwm").html(data.motor0);
    }
}

function initChangeHanlder() {
    $('input[type=range][id=allpwm]').on('change', updateAllSlider);
    $('input[type=range][id=motor1]').on('change', updateSliderPWM);
    $('input[type=range][id=motor2]').on('change', updateSliderPWM);
    $('input[type=range][id=motor3]').on('change', updateSliderPWM);
    $('input[type=range][id=motor4]').on('change', updateSliderPWM);

    $('input[type=radio][name=motorAll]').on('change', switchAllMotor);
    $('input[type=radio][name=motor1]').on('change', switchMotor);
    $('input[type=radio][name=motor2]').on('change', switchMotor);
    $('input[type=radio][name=motor3]').on('change', switchMotor);
    $('input[type=radio][name=motor4]').on('change', switchMotor);
}

$(document).ready(function () {
    $.ajax({
        url: "/getpwm",
        type: 'GET',
        dataType: 'json',
        success: initPwm,
        complete: initChangeHanlder,
        error: function (query, status) {
            console.log(`error: query=${JSON.stringify(query, null, 4)}`);
            console.log(`error: status=${status}`);
        }
    });
});
