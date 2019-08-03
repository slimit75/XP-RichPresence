-- Configuration
spdDisagree = true -- Enables SPD DISAGREE warning.
altDisagree = true -- Enables ALT DISAGREE warning.

-- Do not touch below this line!
discordRPC = require "discordRPC"
startTime = os.time()
aircraft = "N/A"
image = "xp"
version = "v0.8.1"

function refresh()
    acf = get("sim/aircraft/view/acf_descrip")
    acfIcao = PLANE_ICAO
    tailNum = PLANE_TAILNUMBER
    kts = math.floor(get("sim/flightmodel/position/indicated_airspeed")) .. "kts"
    kts2 = math.floor(get("sim/flightmodel/position/indicated_airspeed2")) .. "kts"
    alt = math.floor(get("sim/cockpit2/gauges/indicators/altitude_ft_pilot")) .. "ft"
    alt2 = math.floor(get("sim/cockpit2/gauges/indicators/altitude_ft_copilot")) .. "ft"
    
    if (spdDisagree == true) then
        if (kts ~= kts2) then
            kts = "SPD DISAGREE"
        end
    end

    if (altDisagree == true) then
        if (alt ~= alt2) then
            alt = "ALT DISAGREE"
        end
    end

    if (acfIcao == "E170") or (acfIcao == "E175") or (acfIcao == "E190") or (acfIcao == "E195") then -- Embrear E-Jets
        aircraft = "Embraer " .. acfIcao
        image = "e-jets"
        altDisagree = false
    elseif (acfIcao == "DR40") then -- Robin DR400/DR401
        aircraft = "Robin DR401"
        image = "dr40"
    elseif (acfIcao == "C172") then -- Cessna 172
        aircraft = "Cessna 172 Skyhawk"
        image = "c172"
        altDisagree = false
        spdDisagree = false
    elseif (acfIcao == "B733") or (acfIcao == "B734") or (acfIcao == "B735") or (acfIcao == "B736") or (acfIcao == "B737") or (acfIcao == "B738") or (acfIcao == "B739") then -- 737 Classic & 737NG
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Boeing 737-" .. temp .. "00"
        image = "737ng"
    elseif (acfIcao == "B741") or (acfIcao == "B742") or (acfIcao == "B743") or (acfIcao == "B744") or (acfIcao == "B748") then -- Boeing 747
        temp = string.sub(acfIcao, 4, -1)
        if temp ~= 8 then
            temp = "400"
        end
        aircraft = "Boeing 747-" .. temp
        image = "747"
    elseif (acfIcao == "B748") then -- Boeing 747-8
        aircraft = "Boeing 747-8"
        image = "747"
    elseif (acfIcao == "A318") or (acfIcao == "A319") or (acfIcao == "A320") or (acfIcao == "A321") then -- Airbus A320 Family
        aircraft = "Airbus " .. acfIcao
        image = "a320"
    elseif (acfIcao == "B752") or (acfIcao == "B753") then -- Boeing 757
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Boeing 757-" .. temp .. "00"
        image = "b757"
        altDisagree = false
    elseif (acfIcao == "MD82") or (acfIcao == "MD88") then -- MD80
        aircraft = "McDonnell Douglass " .. acfIcao
        image = "md88"
    elseif (acfIcao == "B712") then -- Boeing 717-200
        aircraft = "Boeing 717-200"
        image = "md88"
    elseif (acfIcao == "D328") or (acfIcao == "J328") then -- Dornier 328/328JET
        aircraft = "Dornier 328"
        image = "d328"
    elseif (acfIcao == "B772") or (acfIcao == "B773") or (acfIcao == "B778") or (acfIcao == "B779")then -- Boeing 777
        temp = string.sub(acfIcao, 4, -1)
        if temp == "2" or temp == "3" then
            temp = temp .. "00"
        end
        aircraft = "Boeing 777-" .. temp
        image = "773"
    elseif (acfIcao == "UAE") then -- Support for Chai112/Chai112-s-Boeing-777-300ER
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Boeing 777-300ER"
        image = "773"
        acfIcao = "B77W"
        altDisagree = false
    elseif (acfIcao == "B77L") then -- Boeing 777F / 777-200LR
        aircraft = "Boeing 777-200LR / 777F"
        image = "773"
        altDisagree = false
    elseif (acfIcao == "B77W") then -- Boeing 777-300ER
        aircraft = "Boeing 777-300ER"
        image = "773"
        altDisagree = false
    elseif (acfIcao == "B762") or (acfIcao == "B763") then -- Boeing 767-200/300
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Boeing 767-" .. temp .. "00"
        image = "773"
        altDisagree = false
    elseif (acfIcao == "B764") then -- Boeing 767-400ER
        aircraft = "Boeing 767-400ER"
        image = "773"
        altDisagree = false
    elseif (acfIcao == "B788") or (acfIcao == "B789") or (acfIcao == "B78X") then -- Boeing 787-8/-9/-10
        temp = string.sub(acfIcao, 4, -1)
        if temp == "X" then
            temp = "10"
        end
        aircraft = "Boeing 787-" .. temp
        image = "787"
        altDisagree = false
    elseif (acfIcao == "A332") or (acfIcao == "A333") then -- Airbus A330-200/-300
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Airbus A330-" .. temp .. "00"
        image = "a330"
    elseif acfIcao == "A337" then -- Airbus A330-700
        aircraft = "Airbus Beluga XL"
        image = "a330"
    elseif (acfIcao == "A338") or (acfIcao == "A339") then -- Airbus A330-800neo/-900neo
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Airbus A330-" .. temp .. "00neo"
        image = "a330"
    elseif acfIcao == "A330" then -- Support for the Rivere A330neo
        aircraft = "Airbus A330-900neo"
        image = "A330"
    elseif (acfIcao == "A342") or (acfIcao == "A343") or (acfIcao == "A345") or (acfIcao == "A346") then -- Airbus A340
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Airbus A340-" .. temp .. "00"
        image = "a340"
    elseif acfIcao == "A340-313x" then -- Random Freeware A340 Support
        aircraft = "Airbus A340-300"
        image = "a340"
    elseif (acfIcao == "A380") or (acfIcao == "A388") then -- A380, with support for the Rivere A380
        aircraft = "Airbus A380-800"
        image = "a380"
    elseif acfIcao == "A359" then
        aircraft = "Airbus A350-900"
        image = "a350"
    elseif acfIcao == "A35K" then
        aircraft = "Airbus A350-1000"
        image = "a350"
    else
        aircraft = acf
    end

    if image ~= "xp" then
        discordRPC.updatePresence({
            ["state"] = alt .. ", " .. kts,
            ["details"] = aircraft,
            ["startTimestamp"] = startTime,
            ["largeImageKey"] = image,
            ["largeImageText"] = acfIcao,
            ["smallImageKey"] = "xp",
            ["smallImageText"] = version
        })
    else
        discordRPC.updatePresence({
            ["state"] = alt .. ", " .. kts,
            ["details"] = aircraft,
            ["startTimestamp"] = startTime,
            ["largeImageKey"] = image,
            ["largeImageText"] = acfIcao,
            ["smallImageText"] = version
        })
    end
end

local function run()
    discordRPC.initialize("579668847846752266", false, "269950")
    do_on_exit("discordRPC.clearPresence()")
    do_often("refresh()")
end

local err = xpcall(run, function(err)
    logMsg("XP-RichPresence: " .. err)
end)