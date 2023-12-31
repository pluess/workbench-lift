function updateAllSlider() {
    var sliderValue = $("#allpwm").val();
    $("text_allpwm").html(sliderValue);
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
    $("#allpwm").val(0).trigger("change");
    $("#offAll").prop("checked", true).change();
}

$(document).ready(function () {
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
});

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
