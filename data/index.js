function upateAll() {
    var sliderValue = $("#allpwm").val();
    $("text_allpwm").html(sliderValue);
    console.log("sliderValue=" + sliderValue);
    for (var i = 1; i <= 4; i++) {
        $("#motor" + i).val(sliderValue).trigger("change");
    }
}

function updateSliderPWM(element) {
    var sliderValue = $(element).val();
    $("#text_" + element.id).html(sliderValue);
    var mode = $("#mode").val();
    console.log("element.id=" + element.id)
    console.log("sliderValue=" + sliderValue);
    console.log("mode=" + mode);
    $.ajax(
        {
            url: "/setpwm",
            data: {
                motor: element.id,
                pwm: sliderValue,
                mode: mode
            },
            type: "GET"
        }
    )
}

function resetFunction() {
    $("#allpwm").val(50).trigger("change");
    for (var i = 1; i <= 4; i++) {
        $("#motor" + i).val(50).trigger("change");
    }
}

function a(event) {
    console.log("got it");
    switch ($(this).val()) {
        case 'bwAll':
            console.log("bwAll");
            break;
        case 'fwAll':
            console.log("fwAll");
            break;
        case 'offAll':
            console.log("offAll");
            break;
    }
}

$(document).ready(function () {
    $('input[type=radio][name=driveAll]').on('change', function () {
        switch ($(this).val()) {
            case 'bwAll':
                console.log("bwAll");
                break;
            case 'fwAll':
                console.log("fwAll");
                break;
            case 'offAll':
                console.log("offAll");
                break;
        }
    });
    $('input[type=radio][name=drive1]').on('change', a);
});

